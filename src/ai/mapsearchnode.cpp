
#include "mapsearchnode.h"
#include "worldmodel.h"

WorldModel *MapSearchNode::wm;
bool MapSearchNode::isBallObs;
bool MapSearchNode::isKickObs;
int  MapSearchNode::selfRobot;

bool MapSearchNode::IsSameState(MapSearchNode &rhs)
{
    // same state in a maze search is simply when (x,y) are the same
    if(vec == rhs.vec)
        return true;
    else
        return false;
}

// Here's the heuristic function that estimates the distance from a Node
// to the Goal.

float MapSearchNode::GoalDistanceEstimate(MapSearchNode &nodeGoal)
{
    return vec.dist(nodeGoal.vec);
}

bool MapSearchNode::IsGoal(MapSearchNode &nodeGoal)
{
    return IsSameState(nodeGoal);
}

// This generates the successors to the given Node. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool MapSearchNode::GetSuccessors(AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node)
{
    //qDebug() << "GetSuccessors";
    //qDebug() << "point" << vec.x << vec.y;

    Vector2D v2invd = Vector2D(100000,100000);
    Vector2D parent = v2invd;
    if(parent_node) parent = parent_node->vec;
    //qDebug() << "parent" << parent.x << parent.y;

    //----------
    Position rpos = wm->ourRobot[selfRobot].pos;
    Vector2D bloc = wm->ball.pos.loc;
    double bang = (bloc - rpos.loc).dir().radian() - rpos.dir;
    if (bang >  M_PI) bang -= 2 * M_PI;
    if (bang < -M_PI) bang += 2 * M_PI;

    if(wm->ball.isValid && (isBallObs || (isKickObs && fabs(bang) > M_PI_4 * 3 / 4)))
    {
        //qDebug() << "ball is obs";
        Circle2D bc(wm->ball.pos.loc, ROBOT_RADIUS + BALL_RADIUS);
        if(bc.contains(vec))
        {
            int    p_count = 8;
            double p_dist = ROBOT_RADIUS * 2 +  BALL_RADIUS;

            for(int i=0; i<p_count; i++)
            {
                Vector2D v(p_dist, p_dist);
                v.rotate(360/p_count * i);
                MapSearchNode node = bc.center() + v;

                if(node.vec != parent) astarsearch->AddSuccessor(node);
            }

            //MapSearchNode ans;
            //ans.vec = vec;
            //ans = vec.dist(ans.vec) < vec.dist(node1.vec) ? ans : node1;

            //qDebug() << "vec in ball obs";
            return true;
        }
    }
    //----------

    auto obs = getObsCircle();
    //@kamin
    wm->navigation_pos.clear();
    //kamin

    for(int i=0; i<obs.size(); i++)//obs.size()//-2// test
    {
        Circle2D obs_circle=obs.at(i);
        int    p_count = 6;
        double p_dist  = obs_circle.radius();//2*ROBOT_RADIUS+BALL_RADIUS; //


        if(i<obs.size()-2){
            for(int j=0; j<p_count; j++)
            {
                Vector2D v(p_dist, p_dist);
                v.rotate(360/p_count * j);
                MapSearchNode node = obs[i].center() + v;
                //kamin
                bool checkNodeInterference = true;

                for(int g=0;g<obs.size();g++)
                {
                    if(obs[g].contains(node.vec))
                    {
                        checkNodeInterference = false;
                    }
                }

                if(checkNodeInterference == true)
                {
                    wm->navigation_pos.append(node.vec);
                //kamout
                    if(node.vec != parent) astarsearch->AddSuccessor(node);
                }
            }
        }
        else{
            int goal_p_count=8;
            for(int j=0; j<goal_p_count; j++)
            {
                Vector2D v(p_dist, p_dist);
                v.rotate(360/goal_p_count * j);
                MapSearchNode node = obs[i].center() + v;
                //kamin
                bool checkNodeInterference = true;

                for(int g=0;g<obs.size();g++)
                {
                    if(obs[g].contains(node.vec))
                    {
                        checkNodeInterference = false;
                    }
                }

                if(checkNodeInterference == true)
                {
                    wm->navigation_pos.append(node.vec);
                //kamout
                    if(node.vec != parent) astarsearch->AddSuccessor(node);
                }
            }
        }
    }


    //test
//    for(int i=obs.size()-2; i<obs.size(); i++)
//    {
//        Circle2D obs_circle=obs.at(i);
//        int    p_count = 8;
//        double p_dist  = obs_circle.radius();//2*ROBOT_RADIUS+BALL_RADIUS; //

//        for(int j=0; j<p_count; j++)
//        {
//            Vector2D v(p_dist, p_dist);
//            v.rotate(360/p_count * j);
//            MapSearchNode node = obs[i].center() + v;
//            //kamin
//           bool checkNodeInterference = true;

//           for(int g=0;g<obs.size();g++)
//            {
//                if(obs[g].contains(node.vec))
//                {
//                    checkNodeInterference = false;
//                }
//            }

//            if(checkNodeInterference == true)
//            {
//                wm->navigation_pos.append(node.vec);
//            //kamout
//                if(node.vec != parent) astarsearch->AddSuccessor(node);
//            }
//        }
//    }


    //test

    MapSearchNode goal;
    goal.vec = astarsearch->GetSolutionEnd()->vec;
    astarsearch->AddSuccessor(goal);

    return true;
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is
// conceptually where we're moving

float MapSearchNode::GetCost(MapSearchNode &successor)
{
    if(IsSameState(successor)) return 0;

    Segment2D seg(vec, successor.vec);
    double d = seg.length();

    auto obs = getObsCircle();
    for(int i=0; i<obs.size(); i++)
    {
        Vector2D sol1, sol2;
        if(obs[i].intersection(seg, &sol1, &sol2) > 1) d += 1000000;
    }

    //qDebug() << "GetCost" << vec.x << vec.y << "TO" << successor.vec.x << successor.vec.y << "=" << d;
    return d;
}


QList<Circle2D> MapSearchNode::getObsCircle()
{
    QList<Circle2D> result;
    double b_rad = ROBOT_RADIUS + 2*BALL_RADIUS+50;
    double r_rad = ROBOT_RADIUS * 2+50;
    if(isBallObs && wm->ball.isValid)
    {
        Circle2D c(wm->ball.pos.loc, b_rad);
        result.append(c);
    }


    if(!isBallObs && isKickObs && wm->ball.isValid)
    {
        Position rpos = wm->ourRobot[selfRobot].pos;
        Vector2D bloc = wm->ball.pos.loc;

        double bang = (bloc - rpos.loc).dir().radian() - rpos.dir;
        if (bang >  M_PI) bang -= 2 * M_PI;//
        if (bang < -M_PI) bang += 2 * M_PI;

        if(fabs(bang) > M_PI_4 * 3 / 4)
        {
            Circle2D c(wm->ball.pos.loc, b_rad);
            result.append(c);
        }
    }

    //kamin
    for(int i=0; i<PLAYERS_MAX_NUM; i++)
    {
        if(i == selfRobot) continue;
        if(!wm->ourRobot[i].isValid) continue;
        //if((wm->ourRobot[i].pos.loc-wm->ourRobot[selfRobot].pos.loc).length() < 500
         //       && (wm->ourRobot[i].vel.loc-wm->ourRobot[selfRobot].vel.loc).length() < 1) continue;
        Circle2D c(wm->ourRobot[i].pos.loc + wm->ourRobot[i].vel.loc * AI_TIMER, r_rad);
        result.append(c);
    }

    for(int i=0; i<PLAYERS_MAX_NUM; i++)
    {
        if(!wm->oppRobot[i].isValid) continue;
        Circle2D c(wm->oppRobot[i].pos.loc+ wm->oppRobot[i].vel.loc * AI_TIMER, r_rad);
        result.append(c);
    }



    Circle2D oppGoal(Field::oppGoalCenter,1000);
    Circle2D ourGoal(Field::ourGoalCenter,1000);

    result.append(oppGoal);
    result.append(ourGoal);


//    for(int i=0; i<wm->predict_pos.size(); i++)
//    {
//        Circle2D c(wm->predict_pos[i], b_rad);
//        qDebug()<<"result size " << result.size();
//        result.append(c);
//        qDebug()<<"result size " << result.size();
//        wm->predict_pos.clear();
//    }


    //kamout

    return result;
}
