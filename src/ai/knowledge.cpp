#include "knowledge.h"
#include "worldmodel.h"

Knowledge::Knowledge(WorldModel *wm, QObject *parent) :
    QObject(parent),
    _wm(wm)
{
    kickPermission=false;
}

int Knowledge::CountActiveAgents()
{
    int counter=0;
    for(int i=0; i< PLAYERS_MAX_NUM; i++)
        if(_wm->ourRobot[i].isValid) counter++;
    return counter;
}

QList<int> Knowledge::ActiveAgents()
{
    QList<int> ans;
    for(int i=0; i< PLAYERS_MAX_NUM; i++)
        if(_wm->ourRobot[i].isValid)
            ans.append(i);
    return ans;
}

QList<int> Knowledge::ActiveOppAgents()
{
    QList<int> ans;
    for(int i=0; i< PLAYERS_MAX_NUM; i++)
        if(_wm->oppRobot[i].isValid)
            ans.append(i);
    return ans;
}

QList<int> Knowledge::findNearestTo(Vector2D loc)
{
    QMap<double, int> smap;
    for(int i=0; i< PLAYERS_MAX_NUM; i++)
    {
        if(_wm->ourRobot[i].isValid==false) continue;
        double dist=(_wm->ourRobot[i].pos.loc-loc).length();
        smap.insert(dist, i);
    }
    QList<int> ans;
    for(auto i=smap.begin(); i!=smap.end(); i++)
        ans.append(i.value());
    return ans;
}

QList<int> Knowledge::findNearestTo(QList<int> ours, Vector2D loc)
{
    QMap<double, int> smap;
    for(int i=0; i< ours.size(); i++)
    {
        if(_wm->ourRobot[ours.at(i)].isValid==false) continue;
        double dist=(_wm->ourRobot[ours.at(i)].pos.loc-loc).length();
        smap.insert(dist, ours.at(i));
    }
    QList<int> ans;
    for(auto i=smap.begin(); i!=smap.end(); i++)
        ans.append(i.value());
    return ans;
}

QList<int> Knowledge::findNearestOppositeTo(Vector2D loc)
{
    QMap<double, int> smap;
    for(int i=0; i< PLAYERS_MAX_NUM; i++)
    {
        if(_wm->oppRobot[i].isValid==false) continue;
        double dist=(_wm->oppRobot[i].pos.loc-loc).length();
        smap.insert(dist, i);
    }
    QList<int> ans;
    for(auto i=smap.begin(); i!=smap.end(); i++)
        ans.append(i.value());
    return ans;
}

QList<int> Knowledge::findNearestOppositeTo(QList<int> opps, Vector2D loc)
{
    QMap<double, int> smap;
    for(int i=0; i< opps.size(); i++)
    {
        if(_wm->oppRobot[opps.at(i)].isValid==false) continue;
        double dist=(_wm->oppRobot[opps.at(i)].pos.loc-loc).length();
        smap.insert(dist, opps.at(i));
    }
    QList<int> ans;
    for(auto i=smap.begin(); i!=smap.end(); i++)
        ans.append(i.value());
    return ans;
}

int Knowledge::findOppAttacker()
{
    int ans=0;
    double mindist=1000000;
    for(int i=0; i< PLAYERS_MAX_NUM; i++)
    {
        if(_wm->oppRobot[i].isValid==false) continue;
        double dist=(_wm->oppRobot[i].pos.loc-_wm->ball.pos.loc).length();
        if(dist<mindist)
        {
            mindist=dist;
            ans=i;
        }
    }
    return ans;
}

void Knowledge::sortOurPlayers(QList<int> &players, Vector2D point, bool ascending)
{
    if( ascending )
    {
        for(int i=0;i<players.size();i++)
        {
            for(int j=i;j<players.size();j++)
            {
                if( (_wm->ourRobot[players.at(j)].pos.loc - point).length()
                        < (_wm->ourRobot[players.at(i)].pos.loc - point).length() )
                {
                    int tmp = players.at(i);
                    players.replace(i,players.at(j));
                    players.replace(j,tmp);
                }
            }
        }
    }
    else
    {
        for(int i=0;i<players.size();i++)
        {
            for(int j=i;j<players.size();j++)
            {
                if( (_wm->ourRobot[players.at(j)].pos.loc - point).length()
                        > (_wm->ourRobot[players.at(i)].pos.loc - point).length() )
                {
                    int tmp = players.at(i);
                    players.replace(i,players.at(j));
                    players.replace(j,tmp);
                }
            }
        }
    }
}

bool Knowledge::IsInsideRect(Vector2D pos, Vector2D topLeft, Vector2D bottomRight)
{
    return (pos.x > topLeft.x && pos.x < bottomRight.x &&
            pos.y > bottomRight.y && pos.y < topLeft.y);
}

bool Knowledge::IsInsideCircle(Vector2D pos, Vector2D center, double radios)
{
    if( (pos-center).length() < radios )
        return true;
    else
        return false;
}

void Knowledge::ClampToRect(Vector2D *pos, Vector2D topLeft, Vector2D bottomRight)
{
    if(pos->x > bottomRight.x)
    {
        pos->x = bottomRight.x;
    }
    else if(pos->x < topLeft.x)
    {
        pos->x = topLeft.x;
    }

    if(pos->y > topLeft.y)
    {
        pos->y = topLeft.y;
    }
    else if(pos->y < bottomRight.y)
    {
        pos->y = bottomRight.y;
    }
}

bool Knowledge::IsInsideField(Vector2D pos)
{
    return IsInsideRect(pos, Field::upperLeftCorner, Field::bottomRightCorner);
}

bool Knowledge::IsInsideOurField(Vector2D pos)
{
    return IsInsideRect(pos, Vector2D(Field::MinX,Field::MaxY), Vector2D(0,Field::MinY));
}

bool Knowledge::IsInsideGoalShape(Vector2D pos, double goalLeftX, double goalRadius, double goalCcOffset)
{
    double x = pos.x - goalLeftX;
    Vector2D ccl(goalLeftX, goalCcOffset / 2), ccr(goalLeftX, -goalCcOffset / 2);

    return ( (pos-ccl).length() <= goalRadius || (pos-ccr).length() <= goalRadius ||
             (x >= 0 && x <= goalRadius && fabs(pos.y) <= goalCcOffset / 2));
}

bool Knowledge::IsInsideGolieArea(Vector2D pos)
{
    return IsInsideGoalShape(pos, Field::ourGoalCenter.x, Field::goalCircle_R,
                             (Field::defenceLineLinear_L-Field::defenceLineLinear_R).length());
}

bool Knowledge::IsInsideSecureArea(Vector2D pos, Vector2D ball)
{
    return IsInsideCircle(pos,ball,ALLOW_NEAR_BALL_RANGE);
}

bool Knowledge::IsInsideOppGolieArea(Vector2D pos)
{
    return IsInsideGoalShape(pos, Field::oppGoalCenter.x, Field::goalCircle_R,350);
}

Vector2D Knowledge::PredictDestination(Vector2D sourcePos, Vector2D targetPos, double sourceSpeed, Vector2D targetSpeed)
{
    double factor = _wm->var[3] / 250.0;
    if(factor < 0)
    {
        factor = 0;
    }

    double Vm = sourceSpeed;
    double k = Vm / targetSpeed.length();
    double gamaT = targetSpeed.dir().radian();
    Vector2D delta;

    delta = targetPos - sourcePos;
    double landa = atan2(delta.y, delta.x);
    double theta = gamaT - landa;

    if (theta > AngleDeg::PI)
    {
        theta -= 2 * AngleDeg::PI;
    }

    if (theta < - AngleDeg::PI)
    {
        theta += 2 * AngleDeg::PI;
    }

    double dlta = 0;
    if(k != 0 && fabs(sin(theta) / k) < 1)
    {
        dlta = asin(sin(theta)/k);
    }
    // No solution.
    else
    {
        qDebug() << "Prediction: No solution.";
        return targetPos;//Vector2D::INVALIDATED;
    }

    double tf = factor * (delta.length() / 1000) / (Vm*cos(dlta) - targetSpeed.length() * cos(theta));

    // No solution.
    if(tf < 0)
    {
        qDebug() << "Prediction: No solution.";
        return targetPos;   //Vector2D(0,0); //INVALIDATED;
    }

    double catchDist = targetSpeed.length() * tf * 1000;
    Vector2D catchDiff(catchDist * cos(gamaT), catchDist * sin(gamaT));
    Vector2D Pred_pos=targetPos + catchDiff;

    //_wm->predict_pos.append(Pred_pos);
    return Pred_pos;
}

bool Knowledge::CanKick(Position robotPos, Vector2D ballPos)
{
    if(!_wm->ball.isValid) return false;

    double distThreshold = _wm->var[0], degThreshold = _wm->var[1] / 10;
    //@kamin
    AngleDeg d1((ballPos + _wm->ball.vel.loc * .015 - robotPos.loc ).dir());
    //@kmout
    AngleDeg d2(robotPos.dir * AngleDeg::RAD2DEG);
    if(fabs((d1 - d2).degree()) < degThreshold || (360.0 - fabs((d1 - d2).degree())) < degThreshold)
    {
        if((robotPos.loc-ballPos).length() < distThreshold)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Knowledge::IsReadyForKick(Position current, Position desired, Vector2D ballPos)
{
    double degThreshold = _wm->var[2] / 10;

    if(fabs((current.dir - desired.dir) * AngleDeg::RAD2DEG) < degThreshold ||
            (360.0 - fabs((current.dir - desired.dir) * AngleDeg::RAD2DEG)) < degThreshold)
    {
        return CanKick(current, ballPos);

    }
    else
    {
        return false;
    }
}

bool Knowledge::ReachedToPos(Vector2D current, Vector2D desired, double distThreshold)
{
    if( (current-desired).length() < distThreshold)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Knowledge::agentIsFree(int index)
{
    QList<int> oppAgents = ActiveOppAgents();
    bool isFree = true;

    while( !oppAgents.isEmpty() )
    {
        int indexOPP = oppAgents.takeFirst();
        if( (_wm->ourRobot[index].pos.loc-_wm->oppRobot[indexOPP].pos.loc).length() < DangerDist)
        {
            isFree = false;
        }

        if(!isFree)
            break;
    }
    return isFree;
}

bool Knowledge::isOccupied(Vector2D input)
{
    for(int i = 0;i<PLAYERS_MAX_NUM;i++)
    {
        if(_wm->ourRobot[i].isValid)
        {
            if( (_wm->ourRobot[i].pos.loc - input).length() < ROBOT_RADIUS+100)
            {
                return true;
            }
        }
    }

    for(int i = 0;i<PLAYERS_MAX_NUM;i++)
    {
        if(_wm->oppRobot[i].isValid)
        {
            if( (_wm->oppRobot[i].pos.loc - input).length() < ROBOT_RADIUS+100)
            {
                return true;
            }
        }
    }

    return false;
}

QString Knowledge::gameStatus()
{
    QString out;

    QList<int> ourNearestPlayerToBall = findNearestTo(_wm->ball.pos.loc);
    QList<int> oppNearestPlayerToBall = findNearestOppositeTo(_wm->ball.pos.loc);

    if( abs(ourNearestPlayerToBall.size() - oppNearestPlayerToBall.size()) < 3 )
    {
        double ourDistance2Ball = (_wm->ourRobot[ourNearestPlayerToBall.at(0)].pos.loc - _wm->ball.pos.loc).length();
        double oppDistance2Ball = (_wm->oppRobot[oppNearestPlayerToBall.at(0)].pos.loc - _wm->ball.pos.loc).length();

        if( ourDistance2Ball - oppDistance2Ball > 300 )
            out = "Attacking";
        else if( oppDistance2Ball - ourDistance2Ball > 300 )
            out = "Defending";
        else
            out = "Not Changed";
    }
    else
    {
        if( ourNearestPlayerToBall.size() - oppNearestPlayerToBall.size() >= 3 )
            out = "Attacking";
        else if( oppNearestPlayerToBall.size() - ourNearestPlayerToBall.size() >= 3 )
            out = "Defending";
    }

    return out;
}

QList<int> Knowledge::findAttackers()
{
    QList<int> output;
    QList<int> ourAgents = _wm->kn->ActiveAgents();

    for(int i=0;i<ourAgents.size();i++)
    {
        if( _wm->ourRobot[ourAgents.at(i)].isValid )
        {
            switch (_wm->ourRobot[ourAgents.at(i)].Role)
            {
            case AgentRole::AttackerMid:
                output.append(ourAgents.at(i));
                break;
            case AgentRole::AttackerLeft:
                output.append(ourAgents.at(i));
                break;
            case AgentRole::AttackerRight:
                output.append(ourAgents.at(i));
                break;
            default:
                break;
            }
        }
    }
    return output;
}

QList<int> Knowledge::findOurObstacles()
{
    QList<int> output;
    QList<int> ourAgents = _wm->kn->ActiveAgents();

    for(int i=0;i<ourAgents.size();i++)
    {
        switch (_wm->ourRobot[ourAgents.at(i)].Role)
        {
        case AgentRole::DefenderMid:
            output.append(ourAgents.at(i));
            break;
        case AgentRole::DefenderLeft:
            output.append(ourAgents.at(i));
            break;
        case AgentRole::DefenderRight:
            output.append(ourAgents.at(i));
            break;
        case AgentRole::Golie:
            output.append(ourAgents.at(i));
            break;
        default:
            break;
        }
    }
    return output;
}

double Knowledge::scoringChance(Vector2D loc)
{
    tANDp out;
    out.prob = 0;

    QList<tANDp> TANDPis;
    int prob=100;
    int dist_Clearance = 30 ; // 3 cm for opp Robot Reaction displacement
    for(int jj=-10;jj<11;jj++)
    {
        Vector2D Point;
        Point.x = Field::oppGoalCenter.x;
        Point.y = Field::oppGoalCenter.y + jj*(Field::oppGoalPost_L.y/10);
        tANDp tp;
        tp.pos=Point;
        int min_prob = 100;
        for(int ii=0;ii<12;ii++)
        {
            if(_wm->oppRobot[ii].isValid)
            {
                if(_wm->oppRobot[ii].pos.loc.x > loc.x)
                {
                    Segment2D ball2Point(loc,Point);
                    double dist2R = ball2Point.dist(_wm->oppRobot[ii].pos.loc);
                    if (dist2R < (ROBOT_RADIUS + BALL_RADIUS + dist_Clearance) ) prob=0;
                    else if (dist2R < 400 ) prob = dist2R/4;
                    else prob = 100;
                    if(prob < min_prob) min_prob = prob;
                }
            }
            if(abs(jj) > 7) prob = prob*((17-abs(jj))/10);
            if(min_prob == 0) break;
        }
        tp.prob=min_prob;
        TANDPis.push_back(tp);
    }

    out = TANDPis.at(0);
    for(int i=1;i<TANDPis.size();i++)
    {
        if( out.prob < TANDPis.at(i).prob)
            out = TANDPis.at(i);
    }
    return out.prob;
}

double Knowledge::oppScoringChance(Vector2D loc)
{
    tANDp out;
    out.prob = 0;

    QList<tANDp> TANDPis;
    int prob=100;
    int dist_Clearance = 30 ; // 3 cm for opp Robot Reaction displacement
    QList<int> our = this->findOurObstacles();
    if( !_wm->kn->IsInsideRect(loc , Vector2D(Field::MaxX/2,Field::MaxY) ,Vector2D(Field::MaxX,Field::MinY)) )
    {
        for(int jj=-10;jj<11;jj++)
        {
            Vector2D Point;
            Point.x = Field::ourGoalCenter.x;
            Point.y = Field::ourGoalCenter.y + jj*(Field::ourGoalPost_L.y/10);
            tANDp tp;
            tp.pos=Point;
            int min_prob = 100;
            for(int ii=0;ii<our.size();ii++)
            {
                if(_wm->ourRobot[our.at(ii)].isValid)
                {
                    if(_wm->ourRobot[our.at(ii)].pos.loc.x < loc.x)
                    {
                        Segment2D ball2Point(loc,Point);
                        double dist2R = ball2Point.dist(_wm->ourRobot[our.at(ii)].pos.loc);
                        if (dist2R < (ROBOT_RADIUS + BALL_RADIUS + dist_Clearance) ) prob=0;
                        else if (dist2R < 400 ) prob = dist2R/4;
                        else prob = 100;
                        if(prob < min_prob) min_prob = prob;
                    }
                }
                if(abs(jj) > 7) prob = prob*((17-abs(jj))/10);
                if(min_prob == 0) break;
            }
            tp.prob=min_prob;
            TANDPis.push_back(tp);
        }
    }
    else
    {
        tANDp tp;
        tp.prob = 0;
        TANDPis.push_back(tp);
    }

    out = TANDPis.at(0);
    for(int i=1;i<TANDPis.size();i++)
    {
        if( out.prob < TANDPis.at(i).prob)
            out = TANDPis.at(i);
    }
    return out.prob;
}

bool Knowledge::ReachedToPos(Position current, Position desired, double distThreshold, double degThreshold)
{
    if( (current.loc-desired.loc).length() < distThreshold)
    {
        if(fabs((current.dir - desired.dir) * AngleDeg::RAD2DEG) < degThreshold ||
                (360.0 - fabs((current.dir - desired.dir) * AngleDeg::RAD2DEG)) < degThreshold)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

Position Knowledge::AdjustKickPoint(Vector2D ballPos, Vector2D target, int kickSpeed)
{
    Position p;
    Vector2D dir = (ballPos - target);//.normalizedVector();
    dir.setLength( ROBOT_RADIUS);

    p.loc = ballPos + dir;
    p.dir = (-dir).dir().radian();


    return p;
}

OperatingPosition Knowledge::AdjustKickPointB(Vector2D ballLoc, Vector2D target, Position robotPos)
{
    OperatingPosition KickPos;
    Vector2D KickDir = (target - ballLoc);
    bool shoot_sensor = true;
    double DirErr;
    double DistErr;
    double BallDir = _wm->ball.vel.loc.dir().radian();

    if(_wm->ball.vel.loc.length()>.2 && (-KickDir.dir().radian()-80)<BallDir && (-KickDir.dir().radian()+80)>BallDir)
    {
        KickPos.pos.dir = BallDir-M_PI;
        if (KickPos.pos.dir > M_PI) KickPos.pos.dir -= 2 * M_PI;
        if (KickPos.pos.dir < -M_PI) KickPos.pos.dir += 2 * M_PI;

        KickPos.pos.loc = ballLoc ;
        qDebug()<<"BallDir"<<BallDir;
    }
    else
    {
        //possession point >>navigation : ON
        KickDir.setLength( ROBOT_RADIUS + BALL_RADIUS*2);
        KickPos.useNav = true ;

        KickPos.pos.dir = KickDir.dir().radian();
        KickPos.pos.loc = ballLoc - KickDir;

        //possession point check
        DirErr = AngleDeg::rad2deg(fabs(KickPos.pos.dir  - robotPos.dir));
        if(DirErr > 360.0)  DirErr = 360.0 - DirErr ;

        DistErr = (KickPos.pos.loc - robotPos.loc).length();
        if(DirErr < 15 && DistErr < BALL_RADIUS*2) kickPermission = true;
        if(DirErr > 19 && DistErr > BALL_RADIUS*3) kickPermission = false;

    }




    if(kickPermission)
    {
        Vector2D ball_vel_change;


        ball_vel_change =_wm->ball.vel.loc - last_ball_vell;
        last_ball_vell = _wm->ball.vel.loc ;

        if(ball_vel_change.length()>0.02)
            shoot_sensor = false;

        //control point >>navigation : OFF
        KickDir.setLength( ROBOT_RADIUS- BALL_RADIUS);
        KickPos.useNav = false ;
        KickPos.pos.dir = KickDir.dir().radian();//(ballLoc - robotPos.loc).dir().radian();//
        KickPos.pos.loc = ballLoc - KickDir;

        DirErr = AngleDeg::rad2deg(fabs(KickPos.pos.dir  - robotPos.dir));
        if(DirErr > 360.0)  DirErr = 360.0 - DirErr ;

        DistErr = (KickPos.pos.loc - robotPos.loc).length();
        //qDebug()<<"A"<<DirErr<<DistErr<<ball_vel_change.length();

        //#kick distance and angel limits
        if(shoot_sensor)//kicking limits when shooting with sensor
        {

        }
        else//kicking limits when shooting without sensor
        {
            if(DirErr < 10 && DistErr < 45)
            {
                KickPos.readyToShoot = true;
                qDebug()<<"shooooooooooooooooooooooooooooooooooooooot";
            }
            else
            {
                KickPos.readyToShoot = false;
            }

        }
        //##kick distance and angel limits
    }
    else
    {
        qDebug()<<"B";
    }

    if(shoot_sensor)//shooting with sensor or without it
    {
        KickPos.kickSpeed=256;
    }
    else
    {
        KickPos.kickSpeed=255;
    }


    return KickPos;
}


