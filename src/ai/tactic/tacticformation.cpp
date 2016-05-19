#include "tacticformation.h"

TacticFormation::TacticFormation(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticDefender", worldmodel, parent)
{

}

RobotCommand TacticFormation::getCommand()
{
    RobotCommand rc;
    if( !wm->ourRobot[this->id].isValid)
        return rc;

    rc.fin_pos = wm->ourRobot[this->id].pos;
    rc.maxSpeed = 3;
    rc.useNav = true;

    if( this->formationType == 1)
    {
        qDebug()<<"=================================";
        qDebug()<<"ID: "<<this->id;
        qDebug()<<"leader: "<<this->leaderID;
        if( findPositionIndex(wm->ourRobot[leaderID].pos) == -1)
        {
            qDebug()<<"append it";
            if( this->leaderID == 0 )
                wm->debug_pos.append(wm->ourRobot[leaderID].pos.loc);
            path.append(wm->ourRobot[leaderID].pos);
        }

        int nextPoint = findPositionIndex(wm->ourRobot[leaderID].pos, 100);
        qDebug()<<"Next Point is: "<<nextPoint;
        if( nextPoint != -1)
        {
            rc.fin_pos = path.at(nextPoint);
            int robotPosID = findPositionIndex(wm->ourRobot[this->id].pos);
            qDebug()<<"robotPosID: "<<robotPosID;
            if( robotPosID != -1 )
            {
                while( robotPosID != path.size()-1 )
                    path.removeLast();
            }
        }
        qDebug()<<"path size: "<<path.size();
    }
    else
    {
        rc.fin_pos.loc = this->fixedPos;
        rc.fin_pos.dir = (rc.fin_pos.loc - wm->ourRobot[this->id].pos.loc).dir().radian();
    }

    return rc;
}

void TacticFormation::setLeaderID(int leaderID)
{
    this->leaderID = leaderID;
}

void TacticFormation::setInformations(int leaderID, int formationType)
{
    setLeaderID(leaderID);
    this->formationType = formationType;
}

void TacticFormation::setFixedPos(Vector2D vec)
{
    this->fixedPos = vec;
}

int TacticFormation::findPositionIndex(Position pos)
{
    qDebug()<<"path size: "<<path.size();
    for(int i = 0; i < path.size(); i++)
    {
        if ( (pos.loc - path.at(i).loc).length() < 20 )
            return i;
    }

    return -1;
}

int TacticFormation::findPositionIndex(Position pos, double threshold)
{
    qDebug()<<"path size: "<<path.size();
    for(int i = 0; i < path.size(); i++)
    {
        if ( abs((pos.loc - path.at(i).loc).length() - threshold) < 100 )
            return i;
    }

    return -1;
}
