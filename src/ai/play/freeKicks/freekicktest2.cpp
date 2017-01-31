#include "freekicktest2.h"
freeKickTest2::freeKickTest2(WorldModel *worldmodel, QObject *parent) :
    freeKick_base(worldmodel,parent)
{
    freeKickStart = false;
    freeKickRegion = fkRegion::RightRegion;
    oppLevel = Level::Beginner;
}

int freeKickTest2::enterCondition(Level level)
{
    if(wm->kn->IsInsideRect(wm->ball.pos.loc,Vector2D(Field::MinX,Field::MaxY),Vector2D(0,Field::MinY))){
        if(oppLevel==level)
            return 700;
        else
            return 100;
    }
}
void freeKickTest2::resetValues()
{
    this->rolesIsInit = false;
}

void freeKickTest2::setPositions()
{
    Position leftDefPos,rightDefPos,goaliePos;
    int leftID = -1, rightID = -1 , midID = -1;
    bool leftNav, rightNav;

    if( wm->ourRobot[previousLeftID].Role != AgentRole::DefenderLeft )
        previousLeftID = -1;

    if( wm->ourRobot[previousRightID].Role != AgentRole::DefenderRight )
        previousRightID = -1;

    if( (wm->ourRobot[tDefenderLeft->getID()].Role == AgentRole::DefenderLeft) && (leftChecker < PresenceCounter) )
    {
        leftID = tDefenderLeft->getID();
        this->previousLeftID = tDefenderLeft->getID();;
    }

    if( wm->ourRobot[tDefenderRight->getID()].Role == AgentRole::DefenderRight && (rightChecker < PresenceCounter) )
    {
        rightID = tDefenderRight->getID();
        this->previousRightID = tDefenderRight->getID();;
    }

    if( leftChecker > PresenceCounter || leftID == -1 || !wm->kn->robotIsIdle(leftID))
    {
        midID = rightID;
        leftID = -1;
    }

    if( rightChecker > PresenceCounter  || rightID == -1 || !wm->kn->robotIsIdle(rightID))
    {
        midID = leftID;
        rightID = -1;
    }

    zonePositions(leftID,rightID,midID,goaliePos,leftDefPos,leftNav,rightDefPos,rightNav);

    tDefenderLeft->setIdlePosition(leftDefPos);
    tDefenderLeft->setUseNav(leftNav);
    tDefenderRight->setIdlePosition(rightDefPos);
    tDefenderRight->setUseNav(rightNav);

    if( leftID != -1)
    {
        if( (wm->kn->robotIsIdle(leftID)) && (wm->ourRobot[leftID].pos.loc - leftDefPos.loc).length() > 250 )
            leftChecker++;
        else
            leftChecker = 0;
    }
    else
    {
        if( !haltedRobotIsInField(previousLeftID) )
            leftChecker = 0;
    }

    if( rightID != -1)
    {
        if( (wm->kn->robotIsIdle(rightID)) && (wm->ourRobot[rightID].pos.loc - rightDefPos.loc).length() > 250 )
            rightChecker++;
        else
            rightChecker = 0;
    }
    else
    {
        if( !haltedRobotIsInField(previousRightID) )
            rightChecker = 0;
    }

    tGolie->setIdlePosition(goaliePos);
    Position leftAttacker,rightAttacker;
    tAttackerMid->setIdlePosition(wm->ourRobot[tAttackerMid->getID()].pos);
    int indexMax=maxOppThreshold();
    int indexMin=minOppThreshold();
    leftAttacker.loc=Vector2D(Field::MaxX*0.5,wm->ourRobot[indexMax].pos.loc.y);
    rightAttacker.loc=Vector2D(Field::MaxX*0.5,wm->ourRobot[indexMin].pos.loc.y);
    leftAttacker.dir=(Field::oppGoalCenter-wm->ourRobot[tAttackerLeft->getID()].pos.loc).dir().radian();
    rightAttacker.dir=(Field::oppGoalCenter-wm->ourRobot[tAttackerRight->getID()].pos.loc).dir().radian();
    leftPos=leftAttacker;
    rightPos=rightAttacker;
    if(checkDistances()){
        recieverID=tAttackerMid->findBestPlayerForPass();
        tAttackerMid->youHavePermissionForKick(recieverID);
    }
    else {
        recieverID=-1;
        tAttackerMid->youDontHavePermissionForKick();
    }
}
int freeKickTest2::maxOppThreshold(){
    int index;
    double max=0;
    QList<int> oppAgent=wm->kn->ActiveOppAgents();
    for(int i=0;i<oppAgent.size();i++){
        if(max<wm->ourRobot[oppAgent.at(i)].pos.loc.y){
            max=wm->ourRobot[oppAgent.at(i)].pos.loc.y;
            index=oppAgent.at(i);
        }
    }
    return index;
}

int freeKickTest2::minOppThreshold(){
    int index;
    double min;
    QList<int> oppAgent=wm->kn->ActiveOppAgents();
    min=oppAgent.at(0);
    for(int i=0;i<oppAgent.size();i++){
        if(min>wm->ourRobot[oppAgent.at(i)].pos.loc.y){
            min=wm->ourRobot[oppAgent.at(i)].pos.loc.y;
            index=oppAgent.at(i);
        }
    }
    return index;
}

bool freeKickTest2::checkDistances()
{
    bool value=false;
    if(tAttackerRight->getID()!=-1 && tAttackerLeft->getID()!=-1 && !wm->ourRobot[tAttackerLeft->getID()].isValid && !wm->ourRobot[tAttackerRight->getID()].isValid)
        if((wm->ourRobot[tAttackerLeft->getID()].pos.loc.y-leftPos.loc.y)<200 && (wm->ourRobot[tAttackerRight->getID()].pos.loc.y-rightPos.loc.y)<200){
            value=true;
        }
    return value;
}

void freeKickTest2::execute()
{
    QList<int> activeAgent=wm->kn->ActiveAgents();
    for(int i=0;i<activeAgent.size();i++)
        setTactics(activeAgent.at(i));
    setPositions();
    tAttackerMid->isKicker(recieverID);
    tAttackerMid->setFreeKickType(kickType::FreekickTest2);
    activeAgent.removeOne(tAttackerMid->getID());
    if(wm->cmgs.ourIndirectKick()){
        if(recieverID!=-1){
            wm->ourRobot[recieverID].Status=AgentStatus::RecievingPass;
            activeAgent.removeOne(recieverID);
        }
    }
    while(activeAgent.size()>0){
        wm->ourRobot[activeAgent.takeFirst()].Status=AgentStatus::Idle;
    }
}
