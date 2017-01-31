#include "playpenaltyopp.h"

PlayPenaltyOpp::PlayPenaltyOpp(WorldModel *worldmodel, QObject *parent) :
    Play("PlayPenaltyOpp", worldmodel, parent)
{
    tGoalie=new TacticGoalie(wm);
    tDefenderRight=new TacticDefender(wm);
    tDefenderLeft=new TacticDefender(wm);
    tDefenderMid=new TacticDefender(wm);
    tAttackerMid = new TacticAttacker(wm);
    tAttackerRight = new TacticAttacker(wm);
    tAttackerLeft = new TacticAttacker(wm);
}

int PlayPenaltyOpp::enterCondition()
{
    if(wm->cmgs.theirPenaltyKick())
        return 100;//100
    else
        return 0;//0
}

void PlayPenaltyOpp::setTactics(int index)
{
    switch (wm->ourRobot[index].Role) {
    case AgentRole::Golie:
        tactics[index] = tGoalie;
        break;
    case AgentRole::DefenderLeft:
        tactics[index] = tDefenderLeft;
        break;
    case AgentRole::DefenderRight:
        tactics[index] = tDefenderRight;
        break;
    case AgentRole::AttackerMid:
        tactics[index] = tAttackerMid;
        break;
    case AgentRole::AttackerLeft:
        tactics[index] = tAttackerLeft;
        break;
    case AgentRole::AttackerRight:
        tactics[index] = tAttackerRight;
        break;
    case AgentRole::DefenderMid:
        tactics[index] = tDefenderMid;
    default:
        break;
    }
}

void PlayPenaltyOpp::setPositions()
{
    Position goaliePos,leftDefPos,rightDefPos,MidDefPos,rightAttackerPos,leftAttackerPos,midAttackerPos;
    if(wm->ball.vel.loc.length()<0.2){
            int kickerId;
            if(wm->kn->findNearestOppositeTo(wm->ball.pos.loc).length()!=0){
                kickerId=wm->kn->findNearestOppositeTo(wm->ball.pos.loc).at(0);
                Line2D shot(wm->ball.pos.loc,wm->oppRobot[kickerId].pos.loc);
                Vector2D GL,GR;
                GL=Field::ourGoalPost_L;
                GR=Field::ourGoalPost_R;
                if(Field::ourGoalPost_L.y>0){
                    GL.y+=200;
                }
                else{
                    GL.y-=200;
                }
                if(Field::ourGoalPost_R.y>0){
                    GR.y+=200;
                }
                else{
                    GR.y-=200;
                }
                Segment2D gLine(GL,GR);
                goaliePos.loc=gLine.intersection(shot);
                if(gLine.contains(goaliePos.loc)==false){
                    goaliePos.loc=Field::ourGoalCenter;
                }
                goaliePos.dir=(wm->ball.pos.loc-goaliePos.loc).dir().radian();
             }
            else{
                goaliePos.loc=Field::ourGoalCenter;
            }
                //
    }
    else{
            Vector2D f;
            Vector2D a;
            f.x=wm->ball.pos.loc.x+wm->ball.vel.loc.x;
            f.y=wm->ball.pos.loc.y+wm->ball.vel.loc.y;
            Line2D shot(wm->ball.pos.loc,f);
            Segment2D gLine(Field::ourGoalPost_L,Field::ourGoalPost_R);
            a=gLine.intersection(shot);
            if(gLine.contains(a)){
                goaliePos.loc=a;
            }
            else{
                goaliePos.loc=Field::ourGoalCenter;
            }
            goaliePos.dir=(wm->ball.pos.loc-goaliePos.loc).dir().radian();
    }
    if(wm->ball.pos.loc.dist(Field::ourGoalCenter)>450){
        if(wm->ourRobot[tGoalie->getID()].pos.loc.dist(goaliePos.loc)>100){
                if(goaliePos.loc.y>Field::ourGoalCenter.y){
                    goaliePos.loc.y+=20;
                }
                if(goaliePos.loc.y<Field::ourGoalCenter.y){
                    goaliePos.loc.y-=20;
                }
        }
    }
    tGoalie->setIdlePosition(goaliePos);
    wm->debug_pos.append(goaliePos.loc);
    //wm->debug_pos.append(goaliePos.loc);   arminTest

    MidDefPos.loc.x=(4*Field::ourGoalCenter.x+Field::oppGoalCenter.x)/5;
    MidDefPos.loc.y=(4*Field::ourGoalCenter.y+Field::oppGoalCenter.y)/5;
    tDefenderMid->setIdlePosition(MidDefPos);

    leftDefPos.loc.x=(4*Field::ourGoalCenter.x+Field::oppGoalCenter.x)/5;
    leftDefPos.loc.y=+500;
    tDefenderLeft->setIdlePosition(leftDefPos);

    rightDefPos.loc.x=(4*Field::ourGoalCenter.x+Field::oppGoalCenter.x)/5;
    rightDefPos.loc.y=-500;
    tDefenderRight->setIdlePosition(rightDefPos);

    rightAttackerPos.loc.x=(2*Field::ourGoalCenter.x+Field::oppGoalCenter.x)/3;
    rightAttackerPos.loc.y=-1500;
    tAttackerRight->setIdlePosition(rightAttackerPos);

    leftAttackerPos.loc.x=(2*Field::ourGoalCenter.x+Field::oppGoalCenter.x)/3;
    leftAttackerPos.loc.y=+1500;
    tAttackerLeft->setIdlePosition(leftAttackerPos);

    midAttackerPos.loc.x=(2*Field::ourGoalCenter.x+Field::oppGoalCenter.x)/3;
    midAttackerPos.loc.y=0;
    tAttackerMid->setIdlePosition(midAttackerPos);


    //wm->debug_pos.append(goaliePos.loc);

}

void PlayPenaltyOpp::initRole()
{
    QList <int> activeAgents=wm->kn->ActiveAgents();

    if(wm->ourRobot[wm->ref_goalie_our].isValid){
        activeAgents.removeOne(wm->ref_goalie_our);
        wm->ourRobot[wm->ref_goalie_our].Role = AgentRole::Golie;
    }

    switch (activeAgents.length()) {

    case 1:
        //wm->ourRobot[wm->kn->ActiveAgents().at(0)].Role=Golie;
        wm->ourRobot[activeAgents.at(0)].Role=DefenderMid;
        break;
    case 2:
        //wm->ourRobot[wm->kn->ActiveAgents().at(0)].Role=Golie;
        wm->ourRobot[activeAgents.at(0)].Role=DefenderRight;
        wm->ourRobot[activeAgents.at(1)].Role=DefenderLeft;
        break;
    case 3:
        //wm->ourRobot[wm->kn->ActiveAgents().at(0)].Role=Golie;
        wm->ourRobot[activeAgents.at(0)].Role=DefenderMid;
        wm->ourRobot[activeAgents.at(1)].Role=DefenderRight;
        wm->ourRobot[activeAgents.at(2)].Role=DefenderLeft;
        break;
    case 4:
        //wm->ourRobot[wm->kn->ActiveAgents().at(0)].Role=Golie;
        wm->ourRobot[activeAgents.at(0)].Role=DefenderMid;
        wm->ourRobot[activeAgents.at(1)].Role=DefenderRight;
        wm->ourRobot[activeAgents.at(2)].Role=DefenderLeft;
        wm->ourRobot[activeAgents.at(3)].Role=AttackerMid;
        break;
    case 5:
        //wm->ourRobot[wm->kn->ActiveAgents().at(0)].Role=Golie;
        wm->ourRobot[activeAgents.at(0)].Role=DefenderMid;
        wm->ourRobot[activeAgents.at(1)].Role=DefenderRight;
        wm->ourRobot[activeAgents.at(2)].Role=DefenderLeft;
        wm->ourRobot[activeAgents.at(3)].Role=AttackerRight;
        wm->ourRobot[activeAgents.at(4)].Role=AttackerLeft;
        break;
    default:
        break;
    }


}

void PlayPenaltyOpp::execute()
{

    QList<int> activeAgents=wm->kn->ActiveAgents();

    initRole();

    for(int i=0;i<activeAgents.size();i++)
    {
        wm->ourRobot[activeAgents.at(i)].Status = AgentStatus::Idle;
    }

    while( !activeAgents.isEmpty() )
    {
        int index = activeAgents.takeFirst();
        setTactics(index);
    }
    wm->debug_pos.clear();
    setPositions();

    //qDebug()<<"FUCK";
}
