#include "knowledge.h"
#include "worldmodel.h"

Knowledge::Knowledge(WorldModel *wm, QObject *parent) :
    QObject(parent),
    _wm(wm)
{
    kickPermission=false;
    this->lastOneTouchStatus = false;
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
    return IsInsideRect(pos, Vector2D(Field::MinX, Field::MaxY), Vector2D(Field::MaxX, Field::MinY));
}

bool Knowledge::IsInsideOurField(Vector2D pos)
{
    return IsInsideRect(pos, Vector2D(Field::MinX,Field::MaxY), Vector2D(0,Field::MinY));
}

bool Knowledge::IsInsideOppField(Vector2D pos)
{
    return IsInsideRect(pos, Vector2D(0,Field::MaxY), Vector2D(Field::MaxX,Field::MinY));
}

bool Knowledge::IsInsideGoalShape(Vector2D pos, double goalLeftX, double goalRadius, double goalCcOffset)
{
    double x = pos.x - goalLeftX;
    Vector2D ccl(goalLeftX, goalCcOffset / 2), ccr(goalLeftX, -goalCcOffset / 2);

    return ( (pos-ccl).length() <= goalRadius || (pos-ccr).length() <= goalRadius ||
             (x >= 0 && x <= goalRadius && fabs(pos.y) <= goalCcOffset / 2));
}

bool Knowledge::IsInsideFarArea(Vector2D pos)
{
    return IsInsideRect(pos, Vector2D(0.25*Field::MaxX,Field::MaxY), Vector2D(Field::MaxX,Field::MinY));
}

bool Knowledge::IsInsideNearArea(Vector2D pos)
{
    return IsInsideRect(pos, Vector2D(Field::MinX,Field::MaxY), Vector2D(0.8*Field::MinX,0.6*Field::MaxY))
            ||
            IsInsideRect(pos, Vector2D(Field::MinX,0.6*Field::MinY), Vector2D(0.8*Field::MinX,Field::MinY));
}

bool Knowledge::IsNearOurGoal(Vector2D pos)
{
    return IsInsideRect(pos, Vector2D(Field::MinX,Field::MaxY), Vector2D(0.25*Field::MinX,Field::MinY));
}

bool Knowledge::IsInsideGolieArea(Vector2D pos)
{
    return IsInsideGoalShape(pos, Field::ourGoalCenter.x, Field::goalCircle_R+2*BALL_RADIUS,
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
        //qDebug() << "Prediction: No solution.";
        return targetPos;//Vector2D::INVALIDATED;
    }

    double tf = factor * (delta.length() / 1000) / (Vm*cos(dlta) - targetSpeed.length() * cos(theta));

    // No solution.
    if(tf < 0)
    {
        //qDebug() << "Prediction: No solution.";
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

bool Knowledge::isOccupied(int id, Vector2D input)
{
    for(int i = 0;i<PLAYERS_MAX_NUM;i++)
    {
        if(_wm->ourRobot[i].isValid)
        {
            if( (_wm->ourRobot[i].pos.loc - input).length() < ROBOT_RADIUS+100 && ( id != i) )
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

bool Knowledge::isDefender(int index)
{
    bool out = false;
    switch (_wm->ourRobot[index].Role)
    {
    case AgentRole::DefenderLeft:
        out = true;
        break;
    case AgentRole::DefenderRight:
        out = true;
        break;
    case AgentRole::DefenderMid:
        out = true;
        break;
    default:
        break;
    }

    return out;
}

QString Knowledge::gameStatus(QString previousState)
{
    QString out;

    QList<int> ourNearestPlayerToBall = findNearestTo(_wm->ball.pos.loc);
    QList<int> oppNearestPlayerToBall = findNearestOppositeTo(_wm->ball.pos.loc);

    if( oppNearestPlayerToBall.size() != 0 && ourNearestPlayerToBall.size() > 0 )
    {
        if( _wm->defenceMode )
        {
            if( abs(ourNearestPlayerToBall.size() - oppNearestPlayerToBall.size()) < 3 )
            {
                double ourDistance2Ball = (_wm->ourRobot[ourNearestPlayerToBall.at(0)].pos.loc - _wm->ball.pos.loc).length();
                double oppDistance2Ball = (_wm->oppRobot[oppNearestPlayerToBall.at(0)].pos.loc - _wm->ball.pos.loc).length();
                double threshould = 0.33*fabs((_wm->ourRobot[ourNearestPlayerToBall.at(0)].pos.loc - _wm->oppRobot[oppNearestPlayerToBall.at(0)].pos.loc).length());
                int ourBallFollower = ourNearestPlayerToBall.at(0);

                if( _wm->kn->IsInsideOppField(_wm->ball.pos.loc) )
                {
                    if( ourDistance2Ball - oppDistance2Ball > threshould )
                    {
                        if( threshould > 100)
                            out = "Defending";
                        else
                            out = previousState;
                    }
                    else if( oppDistance2Ball - ourDistance2Ball > threshould )
                    {
                        if( threshould > 100)
                            out = "Attacking";
                        else
                            out = previousState;
                    }
                    else
                        out = previousState;
                }
                else
                {
                    if( !isDefender(ourBallFollower))
                    {
                        if( threshould < 100 )
                            out = "Defending";
                        else
                        {
                            if( ourDistance2Ball - oppDistance2Ball > threshould )
                                out = "Defending";
                            else if( oppDistance2Ball - ourDistance2Ball > threshould )
                                out = "Attacking";
                            else
                                out = previousState;
                        }
                    }
                    else
                    {
                        QList<int> ourAttackers = findAttackers();
                        QList<int> nearestAttacker = findNearestTo(ourAttackers, _wm->ourRobot[ourBallFollower].pos.loc);
                        double dist2nearestAttacker = 350000;
                        int oppBallFollower = oppNearestPlayerToBall.at(0);

                        if( nearestAttacker.size() > 0 )
                            dist2nearestAttacker = (_wm->ourRobot[nearestAttacker.at(0)].pos.loc - _wm->ourRobot[ourBallFollower].pos.loc).length();
                        double dist2nearestOpposite = (_wm->oppRobot[oppBallFollower].pos.loc - _wm->ourRobot[ourBallFollower].pos.loc).length();

                        if( dist2nearestAttacker - dist2nearestOpposite > 500 )
                            out = "Defending";
                        //                        else if( dist2nearestAttacker > 1.5*dist2nearestOpposite && dist2nearestAttacker > 200 && dist2nearestOpposite > 200)
                        //                            out = "Defending";
                        else
                        {
                            if( ourDistance2Ball - oppDistance2Ball > 200 )
                                out = "Defending";
                            else if( oppDistance2Ball - ourDistance2Ball > 500 )
                                out = "Attacking";
                            else
                                out = previousState;
                        }
                    }
                }
            }
            else
            {
                if( ourNearestPlayerToBall.size() - oppNearestPlayerToBall.size() >= 3 )
                    out = "Attacking";
                else if( oppNearestPlayerToBall.size() - ourNearestPlayerToBall.size() >= 3 )
                    out = "Defending";
            }
        }
        else
        {
            double ourDistance2Ball = (_wm->ourRobot[ourNearestPlayerToBall.at(0)].pos.loc - _wm->ball.pos.loc).length();
            int ourBallFollower = ourNearestPlayerToBall.at(0);
            double oppDistance2Ball = (_wm->oppRobot[oppNearestPlayerToBall.at(0)].pos.loc - _wm->ball.pos.loc).length();
            int oppBallFollower = oppNearestPlayerToBall.at(0);
            if( abs(ourNearestPlayerToBall.size() - oppNearestPlayerToBall.size()) < 3 )
            {
                if( IsInsideOppField(_wm->ball.pos.loc) )
                {
                    if( ourDistance2Ball - oppDistance2Ball > 500 )
                        out = "Defending";
                    else if( oppDistance2Ball - ourDistance2Ball > 200 )
                        out = "Attacking";
                    else
                        out = previousState;
                }
                else
                {
                    if( !isDefender(ourBallFollower))
                    {
                        if( ourDistance2Ball - oppDistance2Ball > 200 )
                            out = "Defending";
                        else if( oppDistance2Ball - ourDistance2Ball > 500 )
                            out = "Attacking";
                        else
                            out = previousState;
                    }
                    else
                    {
                        QList<int> ourAttackers = findAttackers();
                        QList<int> nearestAttacker = findNearestTo(ourAttackers, _wm->ourRobot[ourBallFollower].pos.loc);
                        double dist2nearestAttacker = 350000;
                        if( nearestAttacker.size() > 0 )
                            dist2nearestAttacker = (_wm->ourRobot[nearestAttacker.at(0)].pos.loc - _wm->ourRobot[ourBallFollower].pos.loc).length();
                        double dist2nearestOpposite = (_wm->oppRobot[oppBallFollower].pos.loc - _wm->ourRobot[ourBallFollower].pos.loc).length();

                        if( dist2nearestAttacker - dist2nearestOpposite > 1000 )
                            out = "Defending";
                        //                        else if( dist2nearestAttacker > 1.5*dist2nearestOpposite && dist2nearestAttacker > 200 && dist2nearestOpposite > 200)
                        //                            out = "Defending";
                        else
                        {
                            if( ourDistance2Ball - oppDistance2Ball > 200 )
                                out = "Defending";
                            else if( oppDistance2Ball - ourDistance2Ball > 500 )
                                out = "Attacking";
                            else
                                out = previousState;
                        }
                    }
                }
            }
            else
            {
                if( ourNearestPlayerToBall.size() - oppNearestPlayerToBall.size() >= 3 )
                    out = "Attacking";
                else if( oppNearestPlayerToBall.size() - ourNearestPlayerToBall.size() >= 3 )
                    out = "Defending";
            }
        }
    }
    else
    {
        out = "Attacking";
    }
    return out;
}

int Knowledge::findOppReciever()
{
    int ownerIndex = -1;

    QList<int> opps = ActiveOppAgents();
    opps.removeOne(_wm->ref_goalie_opp);

    QList<double> distance2Prediction;

    if( _wm->ball.isValid )
    {
        for(int i=0;i<opps.size();i++)
        {
            Vector2D predictedPos = _wm->kn->PredictDestination(_wm->oppRobot[opps.at(i)].pos.loc, _wm->ball.pos.loc,_wm->opp_vel,_wm->ball.vel.loc);
            double distance = (predictedPos - _wm->oppRobot[opps.at(i)].pos.loc).length();
            distance2Prediction.append(distance);
        }

        int min_i = -1;
        double min_d = 35000000;

        for(int i=0;i<distance2Prediction.size();i++)
        {
            if( distance2Prediction.at(i) <= min_d )
            {
                min_d = distance2Prediction.at(i);
                min_i = opps.at(i);
            }
        }

        ownerIndex = min_i;
    }

    return ownerIndex;
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

QList<int> Knowledge::findIdleAttackers()
{
    QList<int> output;
    QList<int> ourAgents = _wm->kn->ActiveAgents();

    for(int i=0;i<ourAgents.size();i++)
    {
        if( _wm->ourRobot[ourAgents.at(i)].isValid && _wm->ourRobot[ourAgents.at(i)].Status == AgentStatus::Idle)
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

int Knowledge::findOurLeftDefender()
{
    QList<int> ourAgents = _wm->kn->ActiveAgents();

    for(int i=0;i<ourAgents.size();i++)
    {
        if( _wm->ourRobot[ourAgents.at(i)].Role == AgentRole::DefenderLeft )
            return ourAgents.at(i);
    }
    return -1;
}

int Knowledge::findOurRightDefender()
{
    QList<int> ourAgents = _wm->kn->ActiveAgents();

    for(int i=0;i<ourAgents.size();i++)
    {
        if( _wm->ourRobot[ourAgents.at(i)].Role == AgentRole::DefenderRight )
            return ourAgents.at(i);
    }
    return -1;
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
        Vector2D Point; // 20 Points Are On OppGoal Line And Each Has a Chance To goal
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

bool Knowledge::robotIsIdle(int id)
{
    if( _wm->ourRobot[id].Status == AgentStatus::Idle )
        return true;
    return false;
}

bool Knowledge::isInOneTouch(int kickerID, int recieverID)
{
    if( _wm->ball.isValid && _wm->ourRobot[kickerID].isValid && _wm->ourRobot[recieverID].isValid )
    {
        Vector2D passSenderPos = _wm->ourRobot[kickerID].pos.loc;
        Vector2D OneTouchKickerPos = _wm->ourRobot[recieverID].pos.loc;
        Vector2D passSender2OneTouchKicker = OneTouchKickerPos-passSenderPos;
        Vector2D passSender2Ball = _wm->ball.pos.loc-passSenderPos;
        Line2D *ballVel= new Line2D(_wm->ball.pos.loc,_wm->ball.vel.loc.dir().degree());
        Circle2D checkingCircle(OneTouchKickerPos,ROBOT_RADIUS+500);
//        if(  ( (passSenderPos-OneTouchKickerPos).length2()<(passSenderPos-_wm->ball.pos.loc).length2() )  ||  (fabs(passSender2OneTouchKicker.dir().degree()-passSender2Ball.dir().degree())>30)  ||  (_wm->ball.vel.loc.length()<0.2)  ||  !(checkingCircle.HasIntersection(*ballVel)) )
//        {
//            lastOneTouchStatus = false;
//            return false;
//        }

        lastOneTouchStatus = true;
        return true;
    }

    return lastOneTouchStatus;
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
