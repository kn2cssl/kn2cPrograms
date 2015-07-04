#include "ai.h"
#include "play/playcontrol.h"
#include "play/playfreekickopp.h"
#include "play/playfreekickour.h"
#include "play/playgameon.h"
#include "play/playhalt.h"
#include "play/playkickoffopp.h"
#include "play/playkickoffour.h"
#include "play/playpenaltyopp.h"
#include "play/playpenaltyour.h"
#include "play/playpreparing.h"
#include "play/playstop.h"
#include "play/playtest.h"
#include "play/playtest2.h"

AI::AI(WorldModel *worldmodel, QString field_size, OutputBuffer *outputbuffer, QObject *parent) :
    QObject(parent),
    wm(worldmodel),
    outputbuffer(outputbuffer)
{
    qDebug() << "AI Initialization...";
    connect(&timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));

    Field::setup_consts(field_size);

    udp = new QUdpSocket();
    ip.setAddress("192.168.4.113");

    current_play = 0;
    for(int i=0; i<PLAYERS_MAX_NUM; i++)
        current_tactic[i] = 0;

    firstWait = 0;

    plays.append(new playControl(wm));
    plays.append(new PlayFreeKickOpp(wm));
    plays.append(new PlayFreeKickOur(wm));
    plays.append(new PlayGameOn(wm));
    plays.append(new PlayHalt(wm));
    plays.append(new PlayKickoffOpp(wm));
    plays.append(new PlayKickoffOur(wm));
    plays.append(new PlayPenaltyOpp(wm));
    plays.append(new PlayPenaltyOur(wm));
    plays.append(new PlayStop(wm));
    plays.append(new PlayPreparing(wm));
    plays.append(new PlayTest(wm));
    plays.append(new PlayTest2(wm));
}

void AI::Start()
{
    qDebug() << "AI::Start";
    timer.start(AI_TIMER);
}

void AI::Stop()
{
    qDebug() << "AI::Stop";
    timer.stop();
}

Play* AI::getCurrentPlay()
{
    return current_play;
}

Tactic* AI::getCurrentTactic(int i)
{
    return current_tactic[i];
}

void AI::timer_timeout()
{
    if( firstWait > 5 )
    {
        for(int i=0; i<PLAYERS_MAX_NUM; i++)
        {
            if(!wm->ourRobot[i].isValid)
                wm->ourRobot[i].Role = NoRole;
        }

        int max_i = 0;
        int max_p = 0;
        for(int i=0; i<plays.size(); i++)
        {
            int p = plays[i]->enterCondition();
            if(p > max_p)
            {
                max_i = i;
                max_p = p;
            }
        }

        Play *play = plays[max_i];
        current_play = play;
        play->execute();

        for(int i=0; i<PLAYERS_MAX_NUM; i++)
        {
            Tactic *tactic = play->getTactic(i);
            current_tactic[i] = tactic;
            if(tactic == NULL) continue;
            tactic->setID(i);
            RobotCommand rc = tactic->getCommand();

            wm->ourRobot[i].SendCommand(rc);
            if(i == wm->indexOfUDP)
            {
                if( wm->sendUDP)
                {
                    double out_x,Sout_x;
                    double out_y,Sout_y;
                    double out_w,Sout_w;

                    if( wm->whichUDP == "pos" )
                    {
                        out_x = wm->ourRobot[wm->indexOfUDP].pos.loc.x;
                        out_y = wm->ourRobot[wm->indexOfUDP].pos.loc.y;
                        out_w = wm->ourRobot[wm->indexOfUDP].pos.dir;


                        Sout_x = rc.fin_pos.loc.x;
                        Sout_y = rc.fin_pos.loc.y;
                        Sout_w = rc.fin_pos.dir;

                    }
                    else
                    {
                        out_x = wm->ourRobot[wm->indexOfUDP].vel.loc.x;
                        out_y = wm->ourRobot[wm->indexOfUDP].vel.loc.y;
                    }

                    char* cp = (char*)&out_x ;
                    char* cp2 = (char*)&out_y;
                    char* cp3 = (char*)&out_w;
                    char* cp4 = (char*)&Sout_x ;
                    char* cp5 = (char*)&Sout_y;
                    char* cp6 = (char*)&Sout_w;
                    //point
                    udp->writeDatagram(cp,sizeof(double),ip,33433);
                    udp->writeDatagram(cp2,sizeof(double),ip,33434);
                    udp->writeDatagram(cp3,sizeof(double),ip,33435);
                    //setpoint
                    udp->writeDatagram(cp4,sizeof(double),ip,33433);
                    udp->writeDatagram(cp5,sizeof(double),ip,33434);
                    udp->writeDatagram(cp6,sizeof(double),ip,33435);
                }
            }
        }


        fps.Pulse();
    }
    else
        firstWait++;
}
