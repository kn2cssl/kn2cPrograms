#include "playformations.h"

PlayFormations::PlayFormations(WorldModel *worldmodel, QObject *parent) :
    Play("PlayFormations", worldmodel, parent)
{
    for(int i = 0; i < NUMOFFORMATION; i++)
        tFormation[i] = new TacticFormation(wm);

    tTest = new TacticTest(wm);
    firstCounter = 0;
    secondCounter = 0;
}

int PlayFormations::enterCondition()
{
    return 20000000;
}

void PlayFormations::initRole()
{

}

void PlayFormations::execute()
{
    int formationT = FORMATIONTYPE;
    if( formationT == 1 )
    {
        QList<int> players = wm->kn->ActiveAgents();
        players.removeOne(TEAMLEADER);
        tactics[TEAMLEADER] = tTest;

        if( players.size() > 0)
        {
            //        tFormation[0] = new TacticFormation(wm);
            tFormation[0]->setInformations(TEAMLEADER,FORMATIONTYPE);
            tactics[players.at(0)] = tFormation[0];

            for(int i = 1; i < players.size(); i++)
            {
                //            tFormation[i] = new TacticFormation(wm);
                tFormation[i]->setLeaderID(players.at(i-1));
                tactics[players.at(i)] = tFormation[i];
            }
        }
    }
    else
    {
        wm->debug_pos.clear();
        Circle2D cir(wm->ourRobot[TEAMLEADER].pos.loc, 750);
        int degree1 = firstCounter*0.5;
        int degree2 = secondCounter*0.5 + 90;
        Line2D line1(wm->ourRobot[TEAMLEADER].pos.loc, degree1);
        Line2D line2(wm->ourRobot[TEAMLEADER].pos.loc, degree2);
        Vector2D first, second,third, fourth;
        cir.intersection(line1, &first,&second);
        cir.intersection(line2, &third,&fourth);

        QList<Vector2D> positions;
        positions.append(first);
        positions.append(second);
        positions.append(third);
        positions.append(fourth);

        QList<int> players = wm->kn->ActiveAgents();
        players.removeOne(TEAMLEADER);

        tFormation[0]->setInformations(TEAMLEADER,FORMATIONTYPE);
        Vector2D pos = positions.takeFirst();
        QList<int> sorted = wm->kn->findNearestTo(players,pos);
        tFormation[0]->setFixedPos(pos);
        tactics[sorted.takeFirst()] = tFormation[0];

        int numOfAssignedAgents = 1;
        qDebug()<<"players size: "<<players.size();
        while( players.size() > 0 && numOfAssignedAgents < NUMOFFORMATION)
        {
            tFormation[numOfAssignedAgents]->setInformations(TEAMLEADER,FORMATIONTYPE);
            Vector2D pos = positions.takeFirst();
            QList<int> sorted = wm->kn->findNearestTo(players,pos);
            tFormation[numOfAssignedAgents]->setFixedPos(pos);
            tactics[sorted.at(0)] = tFormation[numOfAssignedAgents];
            players.removeOne(sorted.at(0));
            numOfAssignedAgents++;
        }

        firstCounter++;
        secondCounter++;
    }
}
