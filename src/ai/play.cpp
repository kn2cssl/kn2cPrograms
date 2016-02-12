#include "play.h"

Play::Play(QString name, WorldModel *worldmodel, QObject *parent) :
    QObject(parent),
    name(name)
{
    wm = worldmodel;
    for(int i=0; i<PLAYERS_MAX_NUM; i++)
        tactics[i] = NULL;

    numberOfDef = NUMOFDEFENDERS;

    rolesIsInit = false;

    defenderflag=false;
    defendersflag=false;
    defendermovmentflag=true;
    goalkeepermovmentflag=true;
}

QString Play::getName()
{
    if(param.size() > 0)
        return name + " => " + param;
    else
        return name;
}

Tactic* Play::getTactic(int id)
{
    if(id >= PLAYERS_MAX_NUM || id < 0) return NULL;
    return tactics[id];
}

bool Play::conditionChanged()
{
    bool out;
    QList<int> activeAgents=wm->kn->ActiveAgents();
    if(activeAgents.size() != numberOfPlayers)
    {
        numberOfPlayers = activeAgents.size();
        out = false;
    }
    return out;
}





void Play::zonePositions(int leftID, int RightID, int MidID, Position &goalie, Position &left, bool& leftNav, Position &right, bool& rightNav)
{


    leftNav=true;
    rightNav=true;
    goalie.loc = Field::ourGoalCenter;
    if( leftID != -1 )
        left = wm->ourRobot[leftID].pos;
    if( RightID != -1 )
        right = wm->ourRobot[RightID].pos;

    //variables:

    Vector2D Midpos;
    double Midangel;


    //defence with two players: goalkeeper : defender flag=false
    Vector2D leftspot={-4200,-500};//-4300=Field::ourGoalPostL.x+200
    Vector2D rightspot={-4200,500};//-4300=Field::ourGoalPostR.x+200
    Vector2D ballpos=wm->ball.pos.loc;
    Vector2D ball2ourGoalPostLvec=Field::ourGoalPost_L-ballpos;
    Vector2D ball2ourGoalPostRvec=Field::ourGoalPost_R-ballpos;
    Segment2D goalline(Field::ourGoalPost_R,Field::ourGoalPost_L);
    Segment2D goalkeeperline(leftspot,rightspot);
    Segment2D ourGoaPostR2OurRightCorner(Field::ourGoalPost_R,Field::bottomLeftCorner);
    Segment2D ourGoaPostL2OurLeftCorner(Field::ourGoalPost_L,Field::upperLeftCorner);


    Line2D *ball2ourGoalPostR=new Line2D(ballpos,Field::ourGoalPost_R);
    Line2D *ball2ourGoalPostL= new Line2D(ballpos,Field::ourGoalPost_L);
    Line2D *ball2ourGoalCenter=new Line2D(ballpos,Field::ourGoalCenter);
    Line2D *ball2goal = new Line2D(ballpos,wm->ball.vel.loc.dir().degree());

    Vector2D ball2ourGoalCentervec=Field::ourGoalCenter-ballpos;
    Circle2D dangerousarea(Field::ourGoalCenter,Field::goalCircle_R+500);//goalCircle_R=1000;

    QList<int> oppIds = wm->kn->findNearestOppositeTo(wm->ball.pos.loc);
    Vector2D attackerpos;

    Line2D *attacker2goalline;
    bool oppIsInField;

    if( oppIds.size() == 0 )
    {
        attackerpos={0,0};
        attacker2goalline=new Line2D(attackerpos,0);
        oppIsInField=false;
    }
    else
    {
        attackerpos=wm->oppRobot[oppIds.at(0)].pos.loc;
        attacker2goalline=new Line2D(attackerpos,(wm->oppRobot[oppIds.at(0)].pos.dir*(180/M_PI)));
        oppIsInField=true;
    }


    ////////////////////////////////////////////////////////////for changing the goalkeeper pos according to the pos of defenders..

    //    leftspot={-4300,-500};
    //    rightspot={-4300,500};
    //    addseg();

    ////////////////////////////////////////////////////////////


    Vector2D goallineintersection;//Intersection between  Line 2D from ball in direction of attacker and goallineSeg
    Vector2D goalkeeperlineintersection;//Intersection between  Line 2D from ball in direction of attacker and goalkeeperlineSeg
    Vector2D goal;//will be used as a temperory variable
    //bool oppIsInField;

    //defence with two players: goalkeeper : defender flag=true
    /////////////////////////////////////////////////////////////////////////////
    //defence with two players: defender
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //defence with three player:goalkeeper:defenderflags=false
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    //defence with three player:goalkeeper:defenderflags=true
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    //defence with three player:defenders
    //////////////////////////////////////////////////////////////////////////////////////////////////////

    if(leftID==-1 || RightID==-1)//defence with two players....
    {
        //goalkeeper:
        {
            if(!defenderflag)//defa saro shekl nagerefte....
            {
                float attacker2balldistance;
                if(oppIds.size()>0)
                {
                    attacker2balldistance=((wm->oppRobot[oppIds.at(0)].pos.loc-ballpos)).length();
                }

                if(attacker2balldistance<attackernoticeabledistance  && oppIsInField  &&  goalline.existIntersection(*attacker2goalline))//the attacker wants to attack to safegoalline not goalline...//goalline.existIntersection(*attacker2goalline)
                {

                    qDebug()<<"yesssssssssssssssssssssssssssssssss";
                    goallineintersection=goalline.intersection(*attacker2goalline);
                    goalkeeperlineintersection=goalkeeperline.intersection(*attacker2goalline);

                    Vector2D goalkeeperline2goalline=goallineintersection-goalkeeperlineintersection;
                    Vector2D temp=goalkeeperline2goalline.rotatedVector(90);
                    temp.setLength(ROBOT_RADIUS);
                    Vector2D temp1=wm->ourRobot[wm->ref_goalie_our].pos.loc+temp;
                    Vector2D temp2=wm->ourRobot[wm->ref_goalie_our].pos.loc-temp;

                    Segment2D blocker(temp1,temp2);

                    bool rightside=blocker.existIntersection(*ball2ourGoalPostR);
                    bool leftside=blocker.existIntersection(*ball2ourGoalPostL);

                    if(rightside && !leftside)
                    {
                        Vector2D ball2ourGoalPostRintersection=blocker.intersection(*ball2ourGoalPostR);
                        Vector2D temp=goalkeeperline2goalline.rotatedVector(90);
                        temp.setLength(ROBOT_RADIUS);
                        goal=ball2ourGoalPostRintersection+temp;

                        Line2D *test = new Line2D(goal,ball2ourGoalPostRvec.dir().degree());

                        if(!(goalline.existIntersection(*test)))
                        {
                            goal=ball2ourGoalPostRintersection-temp;
                        }
                    }
                    else if(!rightside && leftside)
                    {
                        Vector2D ball2ourGoalPostLintersection=blocker.intersection(*ball2ourGoalPostL);
                        Vector2D temp=goalkeeperline2goalline.rotatedVector(90);
                        temp.setLength(ROBOT_RADIUS);
                        goal=ball2ourGoalPostLintersection+temp;

                        Line2D *test=new Line2D(goal,ball2ourGoalPostLvec.dir().degree());

                        if(!(goalline.existIntersection(*test)))
                        {
                            goal=ball2ourGoalPostLintersection-temp;
                        }
                    }

                    else if(!rightside && !leftside)
                    {
                        goal=goalkeeperlineintersection;
                    }

                    goalie.loc=goal;


                    goalie.dir=wm->oppRobot[oppIds.at(0)].pos.dir+M_PI;//in the opposite of the attacker...

                    //                        else if(ourGoaPostR2OurRightCorner.existIntersection(*attacker2goalline))
                    //                        {
                    //                            qDebug()<<"right";
                    //                            Vector2D intersection=goalkeeperline.intersection(*ball2ourGoalPostR);

                    //                            Vector2D temp=ball2ourGoalPostRvec.rotatedVector(90);
                    //                            temp.setLength(ROBOT_RADIUS);

                    //                            goal=intersection+temp;

                    //                            Line2D *test=new Line2D(goal,ball2ourGoalPostRvec.dir().degree());

                    //                            if(!(goalline.existIntersection(*test)))
                    //                            {
                    //                                goal=intersection-temp;
                    //                            }

                    //                            goalie.loc=goal;
                    //                            goalie.dir=(ball2ourGoalPostRvec.dir().radian()+M_PI);
                    //                        }

                    //                        else if(ourGoaPostL2OurLeftCorner.existIntersection(*attacker2goalline))
                    //                        {
                    //                            qDebug()<<"left";
                    //                            Vector2D intersection=goalkeeperline.intersection(*ball2ourGoalPostL);

                    //                            Vector2D temp=ball2ourGoalPostLvec.rotatedVector(90);
                    //                            temp.setLength(ROBOT_RADIUS);

                    //                            goal=intersection+temp;

                    //                            Line2D *test=new Line2D(goal,ball2ourGoalPostLvec.dir().degree());

                    //                            if(!(goalline.existIntersection(*test)))
                    //                            {
                    //                                goal=intersection-temp;
                    //                            }

                    //                            goalie.loc=goal;
                    //                            goalie.dir=(ball2ourGoalPostLvec.dir().radian()+M_PI);
                    //                        }

                }

                else
                {
                    qDebug()<<"no";
                    Vector2D ball2goalkeeperlineintersection=goalkeeperline.intersection(*ball2ourGoalCenter);
                    goalie.loc=ball2goalkeeperlineintersection;
                    goalie.dir=ball2ourGoalCentervec.dir().radian()+M_PI;//in the opposite of the attacker...
                }

            }

            else//defa saro shekl gerefte...
            {
                if(wm->ball.pos.loc.y<-100 || wm->ball.pos.loc.y>100)
                {
                    if((ballpos-Field::ourGoalPost_L).length2()>(ballpos-Field::ourGoalPost_R).length2())
                    {
                        Vector2D intersection=goalkeeperline.intersection(*ball2ourGoalPostL);

                        Vector2D temp=ball2ourGoalPostLvec.rotatedVector(90);
                        temp.setLength(ROBOT_RADIUS);

                        goal=intersection+temp;

                        Line2D *test=new Line2D(goal,ball2ourGoalPostLvec.dir().degree());

                        if(!(goalline.existIntersection(*test)))
                        {
                            goal=intersection-temp;
                        }

                        goalie.loc=goal;
                        goalie.dir=(ball2ourGoalPostRvec.dir().radian()+M_PI);
                    }

                    else
                    {
                        Vector2D intersection;
                        intersection=goalkeeperline.intersection(*ball2ourGoalPostR);

                        Vector2D temp=ball2ourGoalPostRvec.rotatedVector(90);
                        temp.setLength(ROBOT_RADIUS);

                        goal=intersection+temp;

                        Line2D *test=new Line2D(goal,ball2ourGoalPostRvec.dir().degree());

                        if(!(goalline.existIntersection(*test)))
                        {
                            goal=intersection-temp;
                        }

                        goalie.loc=goal;
                        goalie.dir=(ball2ourGoalPostRvec.dir().radian()+M_PI);
                    }

                    goalkeepermovmentflag=true;

                }

                else
                {
                    if(goalkeepermovmentflag && wm->ball.isValid)
                    {
                        if((ballpos-Field::ourGoalPost_L).length2()>(ballpos-Field::ourGoalPost_R).length2() )
                        {
                            Vector2D intersection=goalkeeperline.intersection(*ball2ourGoalPostL);

                            Vector2D temp=ball2ourGoalPostLvec.rotatedVector(90);
                            temp.setLength(ROBOT_RADIUS);

                            goal=intersection+temp;

                            Line2D *test=new Line2D(goal,ball2ourGoalPostLvec.dir().degree());

                            if(!(goalline.existIntersection(*test)))
                            {
                                goal=intersection-temp;
                            }

                            goalkeeperlastpos=goal;
                            goalkeeperlastdir=(ball2ourGoalPostRvec.dir().radian()+M_PI);
                        }

                        else
                        {
                            Vector2D intersection;
                            intersection=goalkeeperline.intersection(*ball2ourGoalPostR);

                            Vector2D temp=ball2ourGoalPostRvec.rotatedVector(90);
                            temp.setLength(ROBOT_RADIUS);

                            goal=intersection+temp;

                            Line2D *test=new Line2D(goal,ball2ourGoalPostRvec.dir().degree());

                            if(!(goalline.existIntersection(*test)))
                            {
                                goal=intersection-temp;
                            }
                            goalkeeperlastpos=goal;
                            goalkeeperlastdir=(ball2ourGoalPostRvec.dir().radian()+M_PI);
                        }

                        goalkeepermovmentflag=false;
                    }

                    goalie.loc=goalkeeperlastpos;
                    goalie.dir=goalkeeperlastdir;
                }



            }

        }

        //defender:
        {
            if(wm->ball.pos.loc.y<-100 || wm->ball.pos.loc.y>100)
            {
                if((ballpos-Field::ourGoalPost_L).length2()<(ballpos-Field::ourGoalPost_R).length2())
                {
                    Vector2D temp1,temp2,intersection;
                    dangerousarea.intersection(*ball2ourGoalPostL,&temp1,&temp2);//the intersection between the line from ball to nearer tirack and the defined circle...

                    if(wm->kn->IsInsideField(temp1))
                    {
                        intersection=temp1;
                    }
                    else
                    {
                        intersection=temp2;
                    }



                    Vector2D temp=ball2ourGoalPostLvec.rotatedVector(90);
                    temp.setLength(ROBOT_RADIUS);

                    goal=intersection+temp;

                    Line2D *test=new Line2D(goal,ball2ourGoalPostLvec.dir().degree());

                    if(!(goalline.existIntersection(*test)))//the defender is locating in the wrong pos
                    {
                        goal=intersection-temp;
                    }

                    Midpos=goal;
                    Midangel=(ball2ourGoalPostLvec.dir().radian()+M_PI);
                }

                else
                {
                    Vector2D temp1,temp2,intersection;
                    dangerousarea.intersection(*ball2ourGoalPostR,&temp1,&temp2);//the intersection between the line from ball to nearer tirack and the defined circle...

                    if(wm->kn->IsInsideField(temp1))
                    {
                        intersection=temp1;
                    }
                    else
                    {
                        intersection=temp2;
                    }

                    Vector2D temp=ball2ourGoalPostRvec.rotatedVector(90);
                    temp.setLength(ROBOT_RADIUS);

                    goal=intersection+temp;

                    Line2D *test=new Line2D(goal,ball2ourGoalPostRvec.dir().degree());

                    if(!(goalline.existIntersection(*test)))//the defender is locating in the wrong pos
                    {
                        goal=intersection-temp;
                    }

                    Midpos=goal;
                    Midangel=(ball2ourGoalPostRvec.dir().radian()+M_PI);
                }

                defendermovmentflag=true;

            }

            else
            {
                if(defendermovmentflag  && wm->ball.isValid)
                {
                    if((ballpos-Field::ourGoalPost_L).length2()<(ballpos-Field::ourGoalPost_R).length2())
                    {
                        Vector2D temp1,temp2,intersection;
                        dangerousarea.intersection(*ball2ourGoalPostL,&temp1,&temp2);//the intersection between the line from ball to nearer tirack and the defined circle...

                        if(wm->kn->IsInsideField(temp1))
                        {
                            intersection=temp1;
                        }
                        else
                        {
                            intersection=temp2;
                        }

                        Vector2D temp=ball2ourGoalPostLvec.rotatedVector(90);
                        temp.setLength(ROBOT_RADIUS);

                        goal=intersection+temp;

                        Line2D *test=new Line2D(goal,ball2ourGoalPostLvec.dir().degree());

                        if(!(goalline.existIntersection(*test)))//the defender is locating in the wrong pos
                        {
                            goal=intersection-temp;
                        }

                        defenderlastpos=goal;
                        defenderlastdir=(ball2ourGoalPostLvec.dir().radian()+M_PI);
                    }

                    else
                    {
                        Vector2D temp1,temp2,intersection;
                        dangerousarea.intersection(*ball2ourGoalPostR,&temp1,&temp2);//the intersection between the line from ball to nearer tirack and the defined circle...

                        if(wm->kn->IsInsideField(temp1))
                        {
                            intersection=temp1;
                        }
                        else
                        {
                            intersection=temp2;
                        }

                        Vector2D temp=ball2ourGoalPostRvec.rotatedVector(90);
                        temp.setLength(ROBOT_RADIUS);

                        goal=intersection+temp;

                        Line2D *test=new Line2D(goal,ball2ourGoalPostRvec.dir().degree());

                        if(!(goalline.existIntersection(*test)))//the defender is locating in the wrong pos
                        {
                            goal=intersection-temp;
                        }

                        defenderlastpos=goal;
                        defenderlastdir=(ball2ourGoalPostRvec.dir().radian()+M_PI);
                    }

                    defendermovmentflag=false;

                }

                Midpos=defenderlastpos;
                Midangel=defenderlastdir;

            }




            if(MidID!=-1)
            {
                if(((wm->ourRobot[MidID].pos.loc-Midpos).length())<desireddefenderdistance)
                {
                    defenderflag=true;
                }

                else
                {
                    defenderflag=false;
                }

            }

            else
            {
                defenderflag=false;
            }

        }


        ///////////////////////////////////////////////////////////////////////////////////////check the sitution if the ball is closing to our goal...
        if(goalline.existIntersection(*ball2goal)  &&  wm->ball.vel.loc.length()>0.5)
        {
            //defender:
            Vector2D temp1,temp2,ball2goaldangerousareaintersection,ball2goalgoalkeeperlineintersection;

            dangerousarea.intersection(*ball2goal,&temp1,&temp2);//the intersection between the line from ball to nearer tirack and the defined circle...
            if(wm->kn->IsInsideField(temp1))
            {
                ball2goaldangerousareaintersection=temp1;
            }
            else
            {
                ball2goaldangerousareaintersection=temp2;
            }

            Midpos=ball2goaldangerousareaintersection;
            Midangel=wm->ball.vel.loc.dir().radian()+M_PI;

            //goalkeeper:
            ball2goalgoalkeeperlineintersection=goalkeeperline.intersection(*ball2goal);
            goalie.loc=ball2goalgoalkeeperlineintersection;
            goalie.dir=wm->ball.vel.loc.dir().radian()+M_PI;
        }
        /////////////////////////////////////////////////////////////////////////////////////////



        if(MidID==leftID)
        {
            left.loc=Midpos;
            left.dir=Midangel;
        }
        else
        {
            right.loc=Midpos;
            right.dir=Midangel;
        }


    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    else//defence with three player()
    {
        //goalkeeper:
        {
            if(!defenderflag)//defa saro shekl nagerefte....
            {
                float attacker2balldistance;
                if(oppIds.size()>0)
                {
                    attacker2balldistance=((wm->oppRobot[oppIds.at(0)].pos.loc-ballpos)).length();
                }

                if(attacker2balldistance<attackernoticeabledistance  && oppIsInField  &&  goalline.existIntersection(*attacker2goalline))//the attacker wants to attack to safegoalline not goalline...//goalline.existIntersection(*attacker2goalline)
                {

                    qDebug()<<"yesssssssssssssssssssssssssssssssss";
                    goallineintersection=goalline.intersection(*attacker2goalline);
                    goalkeeperlineintersection=goalkeeperline.intersection(*attacker2goalline);

                    Vector2D goalkeeperline2goalline=goallineintersection-goalkeeperlineintersection;
                    Vector2D temp=goalkeeperline2goalline.rotatedVector(90);
                    temp.setLength(ROBOT_RADIUS);
                    Vector2D temp1=wm->ourRobot[wm->ref_goalie_our].pos.loc+temp;
                    Vector2D temp2=wm->ourRobot[wm->ref_goalie_our].pos.loc-temp;

                    Segment2D blocker(temp1,temp2);

                    bool rightside=blocker.existIntersection(*ball2ourGoalPostR);
                    bool leftside=blocker.existIntersection(*ball2ourGoalPostL);

                    if(rightside && !leftside)
                    {
                        Vector2D ball2ourGoalPostRintersection=blocker.intersection(*ball2ourGoalPostR);
                        Vector2D temp=goalkeeperline2goalline.rotatedVector(90);
                        temp.setLength(ROBOT_RADIUS);
                        goal=ball2ourGoalPostRintersection+temp;

                        Line2D *test = new Line2D(goal,ball2ourGoalPostRvec.dir().degree());

                        if(!(goalline.existIntersection(*test)))
                        {
                            goal=ball2ourGoalPostRintersection-temp;
                        }
                    }
                    else if(!rightside && leftside)
                    {
                        Vector2D ball2ourGoalPostLintersection=blocker.intersection(*ball2ourGoalPostL);
                        Vector2D temp=goalkeeperline2goalline.rotatedVector(90);
                        temp.setLength(ROBOT_RADIUS);
                        goal=ball2ourGoalPostLintersection+temp;

                        Line2D *test=new Line2D(goal,ball2ourGoalPostLvec.dir().degree());

                        if(!(goalline.existIntersection(*test)))
                        {
                            goal=ball2ourGoalPostLintersection-temp;
                        }
                    }

                    else if(!rightside && !leftside)
                    {
                        goal=goalkeeperlineintersection;
                    }

                    goalie.loc=goal;


                    goalie.dir=wm->oppRobot[oppIds.at(0)].pos.dir+M_PI;//in the opposite of the attacker...

                    //                        else if(ourGoaPostR2OurRightCorner.existIntersection(*attacker2goalline))
                    //                        {
                    //                            qDebug()<<"right";
                    //                            Vector2D intersection=goalkeeperline.intersection(*ball2ourGoalPostR);

                    //                            Vector2D temp=ball2ourGoalPostRvec.rotatedVector(90);
                    //                            temp.setLength(ROBOT_RADIUS);

                    //                            goal=intersection+temp;

                    //                            Line2D *test=new Line2D(goal,ball2ourGoalPostRvec.dir().degree());

                    //                            if(!(goalline.existIntersection(*test)))
                    //                            {
                    //                                goal=intersection-temp;
                    //                            }

                    //                            goalie.loc=goal;
                    //                            goalie.dir=(ball2ourGoalPostRvec.dir().radian()+M_PI);
                    //                        }

                    //                        else if(ourGoaPostL2OurLeftCorner.existIntersection(*attacker2goalline))
                    //                        {
                    //                            qDebug()<<"left";
                    //                            Vector2D intersection=goalkeeperline.intersection(*ball2ourGoalPostL);

                    //                            Vector2D temp=ball2ourGoalPostLvec.rotatedVector(90);
                    //                            temp.setLength(ROBOT_RADIUS);

                    //                            goal=intersection+temp;

                    //                            Line2D *test=new Line2D(goal,ball2ourGoalPostLvec.dir().degree());

                    //                            if(!(goalline.existIntersection(*test)))
                    //                            {
                    //                                goal=intersection-temp;
                    //                            }

                    //                            goalie.loc=goal;
                    //                            goalie.dir=(ball2ourGoalPostLvec.dir().radian()+M_PI);
                    //                        }

                }

                else
                {
                    qDebug()<<"no";
                    Vector2D ball2goalkeeperlineintersection=goalkeeperline.intersection(*ball2ourGoalCenter);
                    goalie.loc=ball2goalkeeperlineintersection;
                    goalie.dir=ball2ourGoalCentervec.dir().radian()+M_PI;//in the opposite of the attacker...
                }

            }

            else//defa saro shekl garefte...
            {
                Vector2D temp1,temp2,intersection;
                Vector2D rightpoint;
                Vector2D leftpoint;

                //rightpoint
                {
                    dangerousarea.intersection(*ball2ourGoalPostR,&temp1,&temp2);//the intersection between the line from ball to nearer tirack and the defined circle...
                    if(wm->kn->IsInsideField(temp1))
                    {
                        intersection=temp1;
                    }
                    else
                    {
                        intersection=temp2;
                    }
                    Vector2D temp=ball2ourGoalPostRvec.rotatedVector(90);
                    temp.setLength(2*ROBOT_RADIUS);//radius of robot
                    rightpoint=intersection+temp;

                    Line2D *test=new Line2D(rightpoint,ball2ourGoalPostRvec.dir().degree());

                    if(!(goalline.existIntersection(*test)))//the defender is locating in the wrong pos
                    {
                        rightpoint=intersection-temp;
                    }

                }

                //leftpoint
                {
                    dangerousarea.intersection(*ball2ourGoalPostL,&temp1,&temp2);//the intersection between the line from ball to nearer tirack and the defined circle...
                    if(wm->kn->IsInsideField(temp1))
                    {
                        intersection=temp1;
                    }
                    else
                    {
                        intersection=temp2;
                    }
                    Vector2D temp=ball2ourGoalPostLvec.rotatedVector(90);
                    temp.setLength(2*ROBOT_RADIUS);//radius of robot
                    leftpoint=intersection+temp;

                    Line2D *test=new Line2D(leftpoint,ball2ourGoalPostLvec.dir().degree());

                    if(!(goalline.existIntersection(*test)))//the defender is locating in the wrong pos
                    {
                        leftpoint=intersection-temp;
                    }

                }

                Line2D *ball2rightpoint=new Line2D(ballpos,rightpoint);
                Line2D *ball2leftpoint=new Line2D(ballpos,leftpoint);

                ///////////////////////////////////////////////////////////////////////////////////////for locating the goalkeeper in new place according to the ball pos
                //                for(int i=0;i<segList.size();i++)
                //                {

                //                    //qDebug()<<"numofSeg"<<i;
                //                    goalkeeperline=segList.at(i);

                //                    Vector2D goalkeeperlinerightintersection=goalkeeperline.intersection(*ball2rightpoint);
                //                    Vector2D goalkeeperlinelefttintersection=goalkeeperline.intersection(*ball2leftpoint);

                //                    goal.x=(goalkeeperlinelefttintersection.x+goalkeeperlinerightintersection.x)/2;
                //                    goal.y=(goalkeeperlinelefttintersection.y+goalkeeperlinerightintersection.y)/2;


                //                    //qDebug()<<goal.x<<","<<goal.y;

                //                    Vector2D temp3,temp4,temp;
                //                    Vector2D ballpos2goal=goal-ballpos;

                //                    temp=ballpos2goal.rotatedVector(90);
                //                    temp.setLength(ROBOT_RADIUS);
                //                    temp3=goal+temp;
                //                    temp4=goal-temp;
                //                    Segment2D blocker(temp3,temp4);

                //                    if( blocker.existIntersection(*ball2leftpoint) && blocker.existIntersection(*ball2rightpoint))
                //                    {
                //                        qDebug()<<"generate";
                //                        break;

                //                    }

                //                }

                /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                Vector2D goalkeeperlinerightintersection=goalkeeperline.intersection(*ball2rightpoint);
                Vector2D goalkeeperlinelefttintersection=goalkeeperline.intersection(*ball2leftpoint);

                goal.x=(goalkeeperlinelefttintersection.x+goalkeeperlinerightintersection.x)/2;
                goal.y=(goalkeeperlinelefttintersection.y+goalkeeperlinerightintersection.y)/2;

                //qDebug()<<goal.x<<","<<goal.y;
                Vector2D goal2ballpos=ballpos-goal;
                goalie.loc=goal;
                goalie.dir=goal2ballpos.dir().radian();
            }

        }

        //defenders:
        {
            Vector2D temp1,temp2,intersection;
            Vector2D Leftgoal;
            Vector2D Rightgoal;

            //left defender....
            {
                dangerousarea.intersection(*ball2ourGoalPostL,&temp1,&temp2);//the intersection between the line from ball to nearer tirack and the defined circle...
                if(wm->kn->IsInsideField(temp1))
                {
                    intersection=temp1;
                }
                else
                {
                    intersection=temp2;
                }

                Vector2D temp=ball2ourGoalPostLvec.rotatedVector(90);
                temp.setLength(ROBOT_RADIUS);

                Leftgoal=intersection+temp;

                Line2D *test=new Line2D(Leftgoal,ball2ourGoalPostLvec.dir().degree());

                if(!(goalline.existIntersection(*test)))//the defender is locating in the wrong pos
                {
                    Leftgoal=intersection-temp;

                }
                left.loc=Leftgoal;
                left.dir=(ball2ourGoalPostLvec.dir().radian()+M_PI);
            }
            //right defender
            {
                dangerousarea.intersection(*ball2ourGoalPostR,&temp1,&temp2);//the intersection between the line from ball to nearer tirack and the defined circle...
                if(wm->kn->IsInsideField(temp1))
                {
                    intersection=temp1;
                }
                else
                {
                    intersection=temp2;
                }

                Vector2D temp=ball2ourGoalPostRvec.rotatedVector(90);
                temp.setLength(ROBOT_RADIUS);


                Rightgoal=intersection+temp;


                Line2D *test=new Line2D(Rightgoal,ball2ourGoalPostRvec.dir().degree());

                if(!(goalline.existIntersection(*test)))//the defender is locating in the wrong pos
                {
                    Rightgoal=intersection-temp;
                }
                right.loc=Rightgoal;
                right.dir=(ball2ourGoalPostRvec.dir().radian()+M_PI);
            }

            if(((wm->ourRobot[leftID].pos.loc)-Leftgoal).length()<desiredleftdefenderdistance && ((wm->ourRobot[RightID].pos.loc)-Rightgoal).length()<desiredrightdefenderdistance)
            {
                defendersflag=true;
            }
            else
            {
                defendersflag=false;
            }
        }


        ///////////////////////////////////////////////////////////////////////////////////////check the sitution if the ball is closing to our goal...
        if(goalline.existIntersection(*ball2goal)  &&  wm->ball.vel.loc.length()>0.5)
        {
            //goalkeeper:
            Vector2D ball2goalgoalkeeperlineintersection=goalkeeperline.intersection(*ball2goal);
            goalie.loc=ball2goalgoalkeeperlineintersection;
            goalie.dir=wm->ball.vel.loc.dir().radian()+M_PI;
        }

    }






    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//    if( wm->cmgs.theirPenaltyKick() )
//    {
//        right.loc = Field::oppPenaltyParallelLineCenter;
//        right.loc.y = Field::oppPenaltyParallelLineCenter.y - (Field::MaxY*0.5);
//        rightNav = false;

//        left.loc.x = Field::oppPenaltyParallelLineCenter.x;
//        left.loc.y = Field::oppPenaltyParallelLineCenter.y + (Field::MaxY*0.5);
//        leftNav = false;

//        goalie = goalieInPenalty();
//    }
//    else if( wm->kn->IsInsideGolieArea(wm->ball.pos.loc) && (!wm->cmgs.canKickBall()) )
//    {
//        right.loc.x = Field::ourGoalCenter.x + Field::goalCircle_R + 200;
//        right.loc.y = Field::ourGoalCenter.y - 350;
//        rightNav = true;

//        left.loc.x = Field::ourGoalCenter.x + Field::goalCircle_R + 200;
//        left.loc.y = Field::ourGoalCenter.y + 350;
//        leftNav = true;
//    }
//    else
//    {
//        Vector2D secondPointForGoalie;

//        bool need2newPoints = false;

//        BallOwner_Finded = Find_OppRobot_BallOwner();
//        if(BallOwner_Finded) Player_filter(Player1);
//        Deffence_Geometry_making();

//        Ball_IS_Toward_Goal = Ball_Toward_Goal();
//        bool Two_Deffence=true;
//        if(MidID!=-1) Two_Deffence=false;

//        if(!Ball_IS_Toward_Goal)
//        {
//            leftNav = true; rightNav = true;
//            if(Two_Deffence) // Two Deffences Are Available
//            {
//                secondPointForGoalie = ( wm->ourRobot[leftID].pos.loc + wm->ourRobot[RightID].pos.loc)/2;
//                need2newPoints = !hasPositionForGoalie(secondPointForGoalie);
//                if(!BallOwner_Finded) // NIST dar ekhtiare kesi  >> Ref2b(ball)
//                {
//                    bool Is_AnyOther_Dangerous = false ;
//                    Is_AnyOther_Dangerous = Find_AnyOther_Opp_Dangerous();
//                    if(Is_AnyOther_Dangerous)
//                    {
//                        // Player1 Is Ready To Give A Pass To Player2

//                        Vector2D Dyno_right,Dyno_left,Deff_center;
//                        //                        bool Is_left;
//                        //                        Ref_2Deff_Player2(Player2,Left2,Right2,Deff_center);
//                        Deff_center = Find_Deff_center(Player2.loc);
//                        int Dyno_Id = Find_Dyno_Deffence(leftID,RightID,Deff_center);
//                        //                        Ref_1Deff_Player2(Player2,leftID,RightID,Dyno_Id,Loc);
//                        Ref_2Deff_Player(Player1);

//                        if(Dyno_Id == leftID)// && Is_Player2_Dangerous) // left Deffence Must Go
//                        {
//                            Ref_1Deff_Loc(Player2.loc,leftID,RightID,Dyno_Id,Dyno_left);
//                            Left_loc = Average_Positioning(Left_loc , Dyno_left);
//                        }
//                        else
//                        {
//                            Ref_1Deff_Loc(Player2.loc,leftID,RightID,Dyno_Id,Dyno_right);
//                            Right_loc = Average_Positioning(Dyno_right , Right_loc);
//                        }
//                    }
//                    else Ref_2Deff_Ball(); // !!!!! Will Complete
//                }
//                else //(BallOwner_Finded)
//                {
//                    bool Is_Danger_Player=false;
//                    Is_Danger_Player = Danger_Player_Direction(Player1,200);
//                    if(Is_Danger_Player) Ref_2Deff_Player(Player1);
//                    else // The Ball Owner Player Is Not Toward Our Goal
//                    {
//                        bool Is_anyone_recieve_pass = Find_Pass_Receiver(Player1);
//                        if(Is_anyone_recieve_pass)
//                        {
//                            // Player1 Is Ready To Give A Pass To Player2

//                            Vector2D Dyno_right,Dyno_left,Deff_center;
//                            //                        bool Is_left;
//                            //                        Ref_2Deff_Player2(Player2,Left2,Right2,Deff_center);
//                            Deff_center = Find_Deff_center(Player2.loc);
//                            int Dyno_Id = Find_Dyno_Deffence(leftID,RightID,Deff_center);
//                            //                        Ref_1Deff_Player2(Player2,leftID,RightID,Dyno_Id,Loc);
//                            Ref_2Deff_Player(Player1);

//                            if(Dyno_Id == leftID)// && Is_Player2_Dangerous) // left Deffence Must Go
//                            {
//                                Ref_1Deff_Loc(Player2.loc,leftID,RightID,Dyno_Id,Dyno_left);
//                                Left_loc = Average_Positioning(Left_loc , Dyno_left);
//                            }
//                            else
//                            {
//                                Ref_1Deff_Loc(Player2.loc,leftID,RightID,Dyno_Id,Dyno_right);
//                                Right_loc = Average_Positioning(Dyno_right , Right_loc);
//                            }
//                        }
//                        else // No One Recieve Pass
//                        {
//                            Ref_2Deff_Ball();
//                        }
//                    }
//                    //                Ref_2Deff_Player(Player1);
//                }
//            }
//            else // One Deffence !
//            {
//                secondPointForGoalie = Find_MostDangerous_Goal_Point();

//                if(!BallOwner_Finded) // NIST dar ekhtiare kesi  >> Ref2b(ball)
//                {
//                    Ref_1Deff_Ball(leftID,RightID,MidID);
//                }
//                else //(BallOwner_Finded)
//                {
//                    Ref_1Deff_Player(Player1,leftID,RightID,MidID);
//                }
//                // For Let The Second Deffence Come Back
//                if(MidID==RightID) Ref_1Deff_Loc(wm->ball.pos.loc,leftID,RightID,leftID,Left_loc);
//                else if(MidID==leftID) Ref_1Deff_Loc(wm->ball.pos.loc,leftID,RightID,RightID,Right_loc);
//            }
//            //            Goalie_loc = Find_MostDangerous_Goal_Point();
//            //            qDebug() << " Goalie : ( " << Goalie_loc.x << "," << Goalie_loc.y << ")";
//            //            goalie.loc = Danger_point ;
//        }
//        else // Ball Is Moving To Our Goal
//        {
//            Line2D L2R(Vector2D(Field::ourGoalCenter.x,Field::MaxY),Vector2D(Field::ourGoalCenter.x,Field::MinY));
//            Line2D BV2T(wm->ball.pos.loc,AngleDeg::rad2deg(wm->ball.vel.loc.dir().radian())); //Ball Vell 2 Target
//            Vector2D intersect_Point = L2R.intersection(BV2T);

//            secondPointForGoalie = intersect_Point;

//            rightNav = false; leftNav = false;
//            if(Two_Deffence) Ref_2Deff_Moving_Ball();
//            else Ref_1Deff_Moving_Ball(leftID,RightID,MidID);
//        }

//        //        Ref_2Deff_Moving_Ball();
//        //                Goalie_loc.y = (Field::ourGoalCenter.y + 2*Goalie_loc.y)/3; //
//        //                Goalie_loc.x += 200;
//        //                goalie.loc = Goalie_loc ;
//        left.loc = Left_loc;
//        left.dir = (wm->ourRobot[leftID].pos.loc - Field::ourGoalPost_L).dir().radian();
//        right.loc = Right_loc;
//        right.dir = (wm->ourRobot[RightID].pos.loc - Field::ourGoalPost_R).dir().radian();

//        if( (left.loc-wm->ball.pos.loc).length() < 400)
//            leftNav = false;
//        if( (right.loc-wm->ball.pos.loc).length() < 400)
//            rightNav = false;

//        //Goal Keeper Positions
//        //        qDebug()<<"secondPointForGoalie : "<<secondPointForGoalie.x<<" , "<<secondPointForGoalie.y;
//        if( need2newPoints )
//            secondPointForGoalie = (right.loc + left.loc)/2;

//        goalie = goaliePosition(secondPointForGoalie);

//        //        qDebug() <<"Left Deffence " << left.loc.x << "," << left.loc.y ;
//        //        qDebug() <<"Right Deffence " << right.loc.x << "," << right.loc.y ;
//    }


}


//===========================================================================================
//===========================================================================================
void Play::Player_filter(Position Player)
{
    //    qDebug() << "last DIR : " << last_dir ;
    double diff_dir = last_dir - Player1.dir;
    if(diff_dir>M_PI) diff_dir-=2*M_PI;
    else if(diff_dir<-M_PI) diff_dir+=2*M_PI;
    Player1.dir = Player.dir + (last_dir - Player1.dir)*0.65;
    last_dir=Player1.dir;
    //    qDebug() << "New DIR : " << Player1.dir ;
}
//===========================================================================================
void Play::Ref_2Deff_Player(Position p)
{
    Line2D L2R(Vector2D(Field::ourGoalCenter.x,Field::MaxY),Vector2D(Field::ourGoalCenter.x,-Field::MaxY));
    Line2D B2OT(wm->ball.pos.loc,AngleDeg::rad2deg(p.dir)); //Ball to Opponent Target
    Vector2D intersect_Point = L2R.intersection(B2OT);
    //    qDebug() << "Intersect Point" << intersect_Point.x << " , " << intersect_Point.y;
    //    qDebug() << Field::ourGoalPost_R.y << " , " << Field::ourGoalPost_L.y ;
    if((intersect_Point.y > Field::ourGoalPost_R.y-100) && (intersect_Point.y < Field::ourGoalPost_L.y+100))
    {
        if(p.dir < -M_PI/2 || p.dir > M_PI/2)
        {
            intersect_Point = intersect_Point - Vector2D(0,intersect_Point.y/2);
            Vector2D B2DC = Deffence_center - wm->ball.pos.loc;
            double Rot_ang = (p.dir - B2DC.dir().radian());
            if(Rot_ang>M_PI) Rot_ang-=2*M_PI;
            else if(Rot_ang<-M_PI) Rot_ang+=2*M_PI;

            B2DC.rotate(AngleDeg::rad2deg(Rot_ang*0.2));
            Deffence_center = wm->ball.pos.loc + B2DC ;

            Left_loc = Wall;
            Left_loc.setLength(Wall_length/4);// 3
            if(Dist_2_Deffence<700) Left_loc.setLength(90) ;
            Left_loc = Deffence_center-Left_loc;
            Right_loc = Wall;
            Right_loc.setLength(Wall_length/4);// 3
            if(Dist_2_Deffence<700) Right_loc.setLength(90) ;
            Right_loc = Deffence_center+Right_loc;
        }
    }
    else Ref_2Deff_Ball();

}
//===========================================================================================
void Play::Ref_2Deff_Ball()
{
    Left_loc = Wall;
    Left_loc.setLength(Wall_length/3);
    if(Dist_2_Deffence<700) Left_loc.setLength(90) ;
    Left_loc = Deffence_center-Left_loc;
    Right_loc = Wall;
    Right_loc.setLength(Wall_length/3);
    if(Dist_2_Deffence<700) Right_loc.setLength(90) ;
    Right_loc = Deffence_center+Right_loc;
}
//===========================================================================================
void Play::Ref_2Deff_Player2(Position p, Vector2D &Left_2, Vector2D &Right_2, Vector2D &Deff_center)
{
    Line2D L2R(Vector2D(Field::ourGoalCenter.x,Field::MaxY),Vector2D(Field::ourGoalCenter.x,-Field::MaxY));
    Line2D P2OT(p.loc,AngleDeg::rad2deg(p.dir)); //Player to Opponent Target
    Vector2D intersect_Point = L2R.intersection(P2OT);
    //    qDebug() << "Intersect Point" << intersect_Point.x << " , " << intersect_Point.y;
    //    qDebug() << Field::ourGoalPost_R.y << " , " << Field::ourGoalPost_L.y ;
    if((intersect_Point.y > Field::ourGoalPost_R.y-100) && (intersect_Point.y < Field::ourGoalPost_L.y+100))
    {
        if(p.dir < -M_PI/2 || p.dir > M_PI/2)
        {
            // --------  Defining New Deffence Center ---------------
            double Deffence_Rad=Field::goalCircleDEF_R;
            Vector2D P2GC=(Field::ourGoalCenter-p.loc);
            double Dist_Ball_2_Goal=P2GC.length();//wm->ball.pos.loc-Field::ourGoalCenter).length();
            double New_Dist_2_Deffence;
            Vector2D New_Deffence_center;

            if(Dist_Ball_2_Goal>Deffence_Rad) New_Dist_2_Deffence=Dist_Ball_2_Goal-Deffence_Rad;
            else New_Dist_2_Deffence=-100;

            Vector2D P2LG=(Field::ourGoalPost_L - p.loc);
            Vector2D P2RG=(Field::ourGoalPost_R - p.loc);
            double ang = (P2RG.dir().radian()-P2LG.dir().radian());

            Vector2D P2DC = P2GC; // Defining Player 2 Center Of Deffence
            P2DC.setLength(New_Dist_2_Deffence);
            //            New_Deffence_center = wm->ball.pos.loc+B2DC;

            double Rot_ang = (p.dir - P2DC.dir().radian());
            if(Rot_ang>M_PI) Rot_ang-=2*M_PI;
            else if(Rot_ang<-M_PI) Rot_ang+=2*M_PI;

            P2DC.rotate(AngleDeg::rad2deg(Rot_ang*0.8));
            New_Deffence_center = p.loc + P2DC ;
            Deff_center = New_Deffence_center;

            double New_Wall_length;
            New_Wall_length=2*New_Dist_2_Deffence*tan(ang/2);

            Vector2D New_Wall=P2GC;
            New_Wall.setLength(New_Wall_length); New_Wall.rotate(90);

            Left_2 = New_Wall;
            Left_2.setLength(New_Wall_length/3);
            if(New_Dist_2_Deffence<700) Left_2.setLength(90) ;
            Left_2 = New_Deffence_center-Left_2;
            Right_2 = New_Wall;
            Right_2.setLength(New_Wall_length/3);
            if(New_Dist_2_Deffence<700) Right_2.setLength(90) ;
            Right_2 = New_Deffence_center+Right_2;
        }
    }
    else
    {
        Ref_2Deff_Ball();
        qDebug() << " !!!!!!!!!!!!!!!! PLEAAAAAAAAASE DEBUG ME 1!!!!!!!!!!!!!!!!";
    }
}
//===========================================================================================
void Play::Ref_2Deff_Moving_Ball()
{
    Line2D L2R(Vector2D(Field::ourGoalCenter.x,Field::MaxY),Vector2D(Field::ourGoalCenter.x,-Field::MaxY));
    Line2D BV2T(wm->ball.pos.loc,AngleDeg::rad2deg(wm->ball.vel.loc.dir().radian())); //Ball Vell 2 Target
    Vector2D intersect_Point = L2R.intersection(BV2T);
    intersect_Point.x = intersect_Point.x + 150*sign(intersect_Point.x);
    //    qDebug() << "Intersect Point" << intersect_Point.x << " , " << intersect_Point.y;
    //    qDebug() << Field::ourGoalPost_R.y << " , " << Field::ourGoalPost_L.y ;
    if((intersect_Point.y > Field::ourGoalPost_R.y-100) && (intersect_Point.y < Field::ourGoalPost_L.y+100))
    {
        if(wm->ball.vel.loc.dir().radian() < -M_PI/2 || wm->ball.vel.loc.dir().radian() > M_PI/2)
        {
            // --------  Defining New Deffence Center ---------------
            Goalie_loc = intersect_Point ;
            double Deffence_Rad=Field::goalCircleDEF_R;
            Vector2D B2GC=(Field::ourGoalCenter-wm->ball.pos.loc);
            double Dist_Ball_2_Goal=B2GC.length();//wm->ball.pos.loc-Field::ourGoalCenter).length();
            double New_Dist_2_Deffence;
            Vector2D New_Deffence_center;

            if(Dist_Ball_2_Goal>Deffence_Rad) New_Dist_2_Deffence=Dist_Ball_2_Goal-Deffence_Rad;
            else New_Dist_2_Deffence=-100;

            Vector2D B2LG=(Field::ourGoalPost_L - wm->ball.pos.loc);
            Vector2D B2RG=(Field::ourGoalPost_R - wm->ball.pos.loc);
            double ang = (B2RG.dir().radian()-B2LG.dir().radian());

            Vector2D B2DC = B2GC; // Defining Player 2 Center Of Deffence
            B2DC.setLength(New_Dist_2_Deffence);
            //            New_Deffence_center = wm->ball.pos.loc+B2DC;

            double Rot_ang = (wm->ball.vel.loc.dir().radian() - B2DC.dir().radian());
            if(Rot_ang>M_PI) Rot_ang-=2*M_PI;
            else if(Rot_ang<-M_PI) Rot_ang+=2*M_PI;

            B2DC.rotate(AngleDeg::rad2deg(Rot_ang*0.8));
            New_Deffence_center = wm->ball.pos.loc + B2DC ;
            //            Deff_center = New_Deffence_center;

            //            double New_Wall_length;
            //            New_Wall_length=2*New_Dist_2_Deffence*tan(ang/2);

            Vector2D New_Wall=B2GC;
            New_Wall.setLength(200/*New_Wall_length*/); New_Wall.rotate(90);

            Left_loc = New_Wall;
            Left_loc.setLength(50);//New_Wall_length/3);
            //            if(New_Dist_2_Deffence<700) Left_loc.setLength(90) ;
            Left_loc = New_Deffence_center-Left_loc;
            Right_loc = New_Wall;
            Right_loc.setLength(50);//New_Wall_length/3);
            //            if(New_Dist_2_Deffence<700) Right_loc.setLength(90) ;
            Right_loc = New_Deffence_center+Right_loc;
        }
        else Ref_2Deff_Ball(); // !!
    }
    else Ref_2Deff_Ball();
}
//===========================================================================================
void Play::Ref_1Deff_Player(Position p,int Left_ID,int Right_ID,int Mid_ID)
{
    //    Segment2D LG2RG(Field::ourGoalPost_L,Field::ourGoalPost_R); // Left Goal to Right Goal
    Line2D L2R(Vector2D(Field::ourGoalCenter.x,Field::MaxY),Vector2D(Field::ourGoalCenter.x,-Field::MaxY));
    Line2D P2OT(p.loc,AngleDeg::rad2deg(p.dir)); //Ball to Opponent Target
    Vector2D intersect_Point = L2R.intersection(P2OT);
    //    qDebug() << "Intersect Point" << intersect_Point.x << " , " << intersect_Point.y;
    //    qDebug() << Field::ourGoalPost_R.y << " , " << Field::ourGoalPost_L.y ;
    if(intersect_Point.y < Field::ourGoalPost_R.y-100) intersect_Point.y = Field::ourGoalPost_R.y-100;
    else if(intersect_Point.y > Field::ourGoalPost_L.y+100) intersect_Point.y = Field::ourGoalPost_L.y+100;
    if(p.dir < -M_PI/2 || p.dir > M_PI/2)
    {
        Vector2D P2DC = Deffence_center - p.loc;
        double Rot_ang = (p.dir - P2DC.dir().radian());
        if(Rot_ang>M_PI) Rot_ang-=2*M_PI;
        else if(Rot_ang<-M_PI) Rot_ang+=2*M_PI;

        P2DC.rotate(AngleDeg::rad2deg(Rot_ang*0.75));
        Deffence_center = p.loc + P2DC ;

        if(Mid_ID==Left_ID)
        {
            Left_loc = Wall;
            Left_loc.setLength((Wall_length/4));
            if(Dist_2_Deffence<700) Left_loc.setLength(90) ;
            Left_loc = Deffence_center-Left_loc;
        }
        else if(Mid_ID==Right_ID)
        {
            Right_loc = Wall;
            Right_loc.setLength((Wall_length/4));
            if(Dist_2_Deffence<700) Right_loc.setLength(90) ;
            Right_loc = Deffence_center+Right_loc;
        }
        else
        {
            qDebug() << " !!!!!!!!!!!!!!!! PLEAAAAAAAAASE DEBUG ME 2!!!!!!!!!!!!!!!!";
            Left_loc =Vector2D(0,0);
            Right_loc=Vector2D(0,0);
        }
        //        }
    }
    else
    {
        Ref_1Deff_Ball(Left_ID,Right_ID,Mid_ID);
    }
}
//===========================================================================================
void Play::Ref_1Deff_Ball(int Left_ID, int Right_ID, int Mid_ID)
{

    if(Mid_ID==Left_ID)
    {
        Left_loc = Wall;
        Left_loc.setLength((Wall_length/4));
        if(Dist_2_Deffence<700) Left_loc.setLength(90) ;
        Left_loc = Deffence_center-Left_loc;
        //        qDebug() << "left : " << Left_loc.x;
        //        qDebug() << "Right : " << Right_loc.x;
    }
    else if(Mid_ID==Right_ID)
    {
        Right_loc = Wall;
        Right_loc.setLength((Wall_length/4));
        if(Dist_2_Deffence<700) Right_loc.setLength(90) ;
        Right_loc = Deffence_center+Right_loc;
        //        qDebug() << "Right : " << Right_loc.x;
    }
    else
    {
        qDebug() << "!!!!!!! No Point For Deffence Selected !!!!!!! " ;
        Left_loc =Vector2D(0,0);
        Right_loc=Vector2D(0,0);
    }

}
//===========================================================================================
void Play::Ref_1Deff_Player2(Position p, int Left_ID, int Right_ID, int Mid_ID, Vector2D &Loc)
{

    //    Segment2D LG2RG(Field::ourGoalPost_L,Field::ourGoalPost_R); // Left Goal to Right Goal
    Line2D L2R(Vector2D(Field::ourGoalCenter.x,Field::MaxY),Vector2D(Field::ourGoalCenter.x,-Field::MaxY));
    Line2D P2OT(p.loc,AngleDeg::rad2deg(p.dir)); //Ball to Opponent Target
    Vector2D intersect_Point = L2R.intersection(P2OT);
    //    qDebug() << "Intersect Point" << intersect_Point.x << " , " << intersect_Point.y;
    //    qDebug() << Field::ourGoalPost_R.y << " , " << Field::ourGoalPost_L.y ;
    if(intersect_Point.y < Field::ourGoalPost_R.y-100) intersect_Point.y = Field::ourGoalPost_R.y-100;
    else if(intersect_Point.y > Field::ourGoalPost_L.y+100) intersect_Point.y = Field::ourGoalPost_L.y+100;
    if(p.dir < -M_PI/2 || p.dir > M_PI/2)
    {

        double Deffence_Rad=Field::goalCircleDEF_R;
        Vector2D P2GC=(Field::ourGoalCenter-p.loc);
        double Dist_Ball_2_Goal=P2GC.length();//wm->ball.pos.loc-Field::ourGoalCenter).length();
        double New_Dist_2_Deffence;
        Vector2D New_Deffence_center;

        if(Dist_Ball_2_Goal>Deffence_Rad) New_Dist_2_Deffence=Dist_Ball_2_Goal-Deffence_Rad;
        else New_Dist_2_Deffence=-100;

        Vector2D P2LG=(Field::ourGoalPost_L - p.loc);
        Vector2D P2RG=(Field::ourGoalPost_R - p.loc);
        double ang = (P2RG.dir().radian()-P2LG.dir().radian());

        Vector2D P2DC = P2GC; // Defining Ball 2 Center Of Deffence
        P2DC.setLength(New_Dist_2_Deffence);
        //            New_Deffence_center = wm->ball.pos.loc+B2DC;
        // -----------------------------------------------------
        double Rot_ang = (p.dir - P2DC.dir().radian());
        if(Rot_ang>M_PI) Rot_ang-=2*M_PI;
        else if(Rot_ang<-M_PI) Rot_ang+=2*M_PI;
        P2DC.rotate(AngleDeg::rad2deg(Rot_ang*0.75));
        New_Deffence_center = p.loc + P2DC ;

        double New_Wall_length;
        New_Wall_length=2*New_Dist_2_Deffence*tan(ang/2);
        Vector2D New_Wall=P2GC;
        New_Wall.setLength(New_Wall_length);
        New_Wall.rotate(90);

        if(Mid_ID==Left_ID)
        {
            Loc = New_Wall;
            Loc.setLength((New_Wall_length/4));
            if(New_Dist_2_Deffence<700) Loc.setLength(90) ;
            Loc = New_Deffence_center-Loc;
            //            Is_left = true ;
            //        qDebug() << "left : " << Left_loc.x;
        }
        else if(Mid_ID==Right_ID)
        {
            Loc = New_Wall;
            Loc.setLength((New_Wall_length/4));
            if(New_Dist_2_Deffence<700) Loc.setLength(90) ;
            Loc = New_Deffence_center-Loc;
            //            Is_left = false ;
        }
        else
        {
            qDebug() << "!!!!!!! No Point For Deffence Selected !!!!!!! " ;
            Loc =Vector2D(0,0);
            Loc=Vector2D(0,0);
        }
        //        }
    }
}
//===========================================================================================
void Play::Ref_1Deff_Moving_Ball(int Left_ID,int Right_ID,int Mid_ID)
{
    Line2D L2R(Vector2D(Field::ourGoalCenter.x,Field::MaxY),Vector2D(Field::ourGoalCenter.x,-Field::MaxY));
    Line2D BV2T(wm->ball.pos.loc,AngleDeg::rad2deg(wm->ball.vel.loc.dir().radian())); //Ball Vell 2 Target
    Vector2D intersect_Point = L2R.intersection(BV2T);
    //    intersect_Point.x = intersect_Point.x + 150*sign(intersect_Point.x);
    //    qDebug() << "Intersect Point" << intersect_Point.x << " , " << intersect_Point.y;
    //    qDebug() << Field::ourGoalPost_R.y << " , " << Field::ourGoalPost_L.y ;
    if((intersect_Point.y > Field::ourGoalPost_R.y-200) && (intersect_Point.y < Field::ourGoalPost_L.y+200))
    {
        if(wm->ball.vel.loc.dir().radian() < -M_PI/2 || wm->ball.vel.loc.dir().radian() > M_PI/2)
        {
            Goalie_loc = intersect_Point ;
            // --------  Defining New Deffence Center ---------------
            double Deffence_Rad=Field::goalCircleDEF_R;
            Vector2D B2GC=(Field::ourGoalCenter-wm->ball.pos.loc);
            double Dist_Ball_2_Goal=B2GC.length();//wm->ball.pos.loc-Field::ourGoalCenter).length();
            double New_Dist_2_Deffence;

            if(Dist_Ball_2_Goal>Deffence_Rad) New_Dist_2_Deffence=Dist_Ball_2_Goal-Deffence_Rad;
            else New_Dist_2_Deffence=-100;

            Vector2D B2DC = B2GC; // Defining Ball Target Center Of Deffence
            B2DC.setLength(New_Dist_2_Deffence);

            double Rot_ang = (wm->ball.vel.loc.dir().radian() - B2DC.dir().radian());
            if(Rot_ang>M_PI) Rot_ang-=2*M_PI;
            else if(Rot_ang<-M_PI) Rot_ang+=2*M_PI;

            Vector2D New_Deffence_center;
            B2DC.rotate(AngleDeg::rad2deg(Rot_ang*1.0));
            New_Deffence_center = wm->ball.pos.loc + B2DC ;

            if(Mid_ID==Left_ID)  Left_loc = New_Deffence_center;
            else if(Mid_ID==Right_ID)  Right_loc = New_Deffence_center;
            else qDebug() << " Check 1 Deff Moving Ball  ! 1 " ;
        }
        else Ref_1Deff_Ball(Left_ID,Right_ID,Mid_ID); // !!!
    }
    else Ref_1Deff_Ball(Left_ID,Right_ID,Mid_ID);
}
//===========================================================================================
void Play::Ref_2Deff_Loc(Vector2D loc) // ball2goal >> loc2goal
{
    double Dist_2_Deffence_loc,Wall_length_Loc;
    Vector2D Deffence_center_loc,Wall_Loc;
    double Deffence_Rad=Field::goalCircleDEF_R;
    Vector2D L2GC=(Field::ourGoalCenter-loc);
    double Dist_Loc_2_Goal=L2GC.length();//wm->ball.pos.loc-Field::ourGoalCenter).length();

    if(Dist_Loc_2_Goal > Deffence_Rad) Dist_2_Deffence_loc = Dist_Loc_2_Goal-Deffence_Rad;
    else Dist_2_Deffence_loc = -100;



    Vector2D L2LG=(Field::ourGoalPost_L - loc);
    Vector2D L2RG=(Field::ourGoalPost_R - loc);
    double ang = (L2RG.dir().radian()-L2LG.dir().radian());
    Vector2D L2DC=L2GC; // Defining Ball 2 Center Of Deffence
    L2DC.setLength(Dist_2_Deffence_loc);
    Deffence_center_loc = loc + L2DC;
    Wall_length_Loc=2*Dist_2_Deffence_loc*tan(ang/2); // length of Deffence Wall which fully protected goal
    Wall_Loc = L2GC;
    Wall_Loc.setLength(Wall_length_Loc); Wall_Loc.rotate(90);

    Left_loc = Wall_Loc;
    Left_loc.setLength(Wall_length_Loc/3);
    if(Dist_2_Deffence_loc<700) Left_loc.setLength(90) ;
    Left_loc = Deffence_center_loc-Left_loc;
    Right_loc = Wall_Loc;
    Right_loc.setLength(Wall_length_Loc/3);
    if(Dist_2_Deffence_loc<700) Right_loc.setLength(90) ;
    Right_loc = Deffence_center_loc+Right_loc;
}
//===========================================================================================
void Play::Ref_1Deff_Loc(Vector2D loc, int Left_ID, int Right_ID, int Mid_ID, Vector2D &Loc)
{
    double Dist_2_Deffence_loc,Wall_length_Loc;
    Vector2D Deffence_center_loc,Wall_Loc;
    double Deffence_Rad=Field::goalCircleDEF_R;
    Vector2D L2GC=(Field::ourGoalCenter-loc);
    double Dist_Loc_2_Goal=L2GC.length();//wm->ball.pos.loc-Field::ourGoalCenter).length();

    if(Dist_Loc_2_Goal > Deffence_Rad) Dist_2_Deffence_loc = Dist_Loc_2_Goal-Deffence_Rad;
    else Dist_2_Deffence_loc = -100;

    Vector2D L2LG=(Field::ourGoalPost_L - loc);
    Vector2D L2RG=(Field::ourGoalPost_R - loc);
    double ang = (L2RG.dir().radian()-L2LG.dir().radian());
    Vector2D L2DC=L2GC; // Defining Ball 2 Center Of Deffence
    L2DC.setLength(Dist_2_Deffence_loc);
    Deffence_center_loc = loc + L2DC;
    Wall_length_Loc=2*Dist_2_Deffence_loc*tan(ang/2); // length of Deffence Wall which fully protected goal
    Wall_Loc = L2GC;
    Wall_Loc.setLength(Wall_length_Loc); Wall_Loc.rotate(90);

    if(Mid_ID==Left_ID)
    {
        Loc = Wall_Loc;
        Loc.setLength((Wall_length_Loc/4));
        if(Dist_2_Deffence_loc<700) Loc.setLength(90) ;
        Loc = Deffence_center_loc-Loc;
        //        qDebug() << "left : " << Left_loc.x;
    }
    else if(Mid_ID==Right_ID)
    {
        Loc = Wall_Loc;
        Loc.setLength((Wall_length_Loc/4));
        if(Dist_2_Deffence_loc<700) Loc.setLength(90) ;
        Loc = Deffence_center_loc+Loc;
    }
    else
    {
        qDebug() << "!!!!!!! No Point For Deffence Selected !!!!!!! " ;
        Loc =Vector2D(0,0);
        //        Right_loc=Vector2D(0,0);
    }


}
//===========================================================================================
bool Play::Danger_Player_Direction(Position p, int thr)
{
    bool is_dangerous=false;
    Vector2D Intersect_Point;
    Line2D L2R(Vector2D(Field::ourGoalCenter.x,Field::MaxY),Vector2D(Field::ourGoalCenter.x,-Field::MaxY));
    Line2D P2OT(p.loc,AngleDeg::rad2deg(p.dir)); //Player to Opponent Target
    Intersect_Point = L2R.intersection(P2OT);
    if((Intersect_Point.y > Field::ourGoalPost_R.y-thr) && (Intersect_Point.y < Field::ourGoalPost_L.y+thr))
    {
        if(p.dir < -M_PI/2 || p.dir > M_PI/2)  is_dangerous = true;

    }
    if(wm->ball.vel.loc.length() > 0.5)
    {
        is_dangerous = false ;
    }

    return is_dangerous;
}
//===========================================================================================
bool Play::Ball_Toward_Goal()
{
    bool To_Goal=false;
    if(wm->ball.vel.loc.length()>0.2)
    {
        Vector2D Intersect_Point;
        //    Segment2D LG2RG(Field::ourGoalPost_L,Field::ourGoalPost_R); // Left Goal to Right Goal
        Line2D L2R(Vector2D(Field::ourGoalCenter.x,Field::MaxY),Vector2D(Field::ourGoalCenter.x,-Field::MaxY));
        Line2D B2T(wm->ball.pos.loc,AngleDeg::rad2deg(wm->ball.vel.loc.dir().radian())); //Ball to Target
        Intersect_Point = L2R.intersection(B2T);
        if((Intersect_Point.y > Field::ourGoalPost_R.y-200) && (Intersect_Point.y < Field::ourGoalPost_L.y+200))
        {
            //            qDebug() << " OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOy !!";
            if(wm->ball.vel.loc.dir().radian() < -M_PI/2 || wm->ball.vel.loc.dir().radian() > M_PI/2)
            {

                To_Goal = true;
                //                qDebug() << " OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO Ball Is Moving Toward Goal" ;
            }
        }
    }
    return To_Goal;
}

bool Play::hasPositionForGoalie(Vector2D midOfDef)
{
    bool output = false;

    if( wm->ball.isValid )
    {
        int picOfCir = 500;
        int marginFromGoalPost = 300;

        double halfOfGoal = (Field::ourGoalPost_L.y-Field::ourGoalPost_R.y)/2;

        Circle2D goalCir(Vector2D(Field::MinX-halfOfGoal-marginFromGoalPost+picOfCir, 0), halfOfGoal + marginFromGoalPost);
        Line2D ball2DefCenter(midOfDef, wm->ball.pos.loc);
        Vector2D first, second, main;
        int numOfPoints = goalCir.intersection(ball2DefCenter, &first, &second);

        bool pointFounded = false;

        if( numOfPoints == 2)
        {
            if( wm->kn->IsInsideField(first) && wm->kn->IsInsideField(second))
            {
                double f2b = ( wm->ball.pos.loc - first).length();
                double s2b = ( wm->ball.pos.loc - second).length();
                if( s2b > f2b)
                    main = first;
                else
                    main = second;

                pointFounded = true;
            }
            else
            {
                if( wm->kn->IsInsideField(first) )
                {
                    main = first;
                    pointFounded = true;
                }
                else if( wm->kn->IsInsideField(second) )
                {
                    main = second;
                    pointFounded = true;
                }
            }
        }
        else if( numOfPoints == 1)
        {
            if( wm->kn->IsInsideField(first) )
            {
                main = first;
                pointFounded = true;
            }
        }
        output = pointFounded;
    }

    return output;
}

Position Play::goaliePosition(Vector2D midOfDef)
{
    Position output;

    if( wm->ball.isValid )
    {
        int picOfCir = PICOFCIR;
        int marginFromGoalPost = MARGINFROMGOALPOST;

        double halfOfGoal = (Field::ourGoalPost_L.y-Field::ourGoalPost_R.y)/2;

        Circle2D goalCir(Vector2D(Field::MinX-halfOfGoal-marginFromGoalPost+picOfCir, 0), halfOfGoal + marginFromGoalPost);
        Line2D ball2DefCenter(midOfDef, wm->ball.pos.loc);
        Vector2D first, second, main;
        int numOfPoints = goalCir.intersection(ball2DefCenter, &first, &second);

        bool pointFounded = false;

        if( numOfPoints == 2)
        {
            if( wm->kn->IsInsideField(first) && wm->kn->IsInsideField(second))
            {
                double f2b = ( wm->ball.pos.loc - first).length();
                double s2b = ( wm->ball.pos.loc - second).length();
                if( s2b > f2b)
                    main = first;
                else
                    main = second;

                pointFounded = true;
            }
            else
            {
                if( wm->kn->IsInsideField(first) )
                {
                    main = first;
                    pointFounded = true;
                }
                else if( wm->kn->IsInsideField(second) )
                {
                    main = second;
                    pointFounded = true;
                }
            }
        }
        else if( numOfPoints == 1)
        {
            if( wm->kn->IsInsideField(first) )
            {
                main = first;
                pointFounded = true;
            }
        }

        if( !pointFounded )
        {
            Line2D ball2OurGoal(Field::ourGoalCenter, wm->ball.pos.loc);
            Vector2D first2, second2, main2;
            int numOfPoints2 = goalCir.intersection(ball2OurGoal, &first2, &second2);

            if( numOfPoints2 == 2)
            {
                if( wm->kn->IsInsideField(first2) )
                    main2 = first2;
                else if( wm->kn->IsInsideField(second2) )
                    main2 = second2;
            }
            else if( numOfPoints2 == 1)
            {
                if( wm->kn->IsInsideField(first2) )
                    main2 = first2;
            }

            main = main2;
        }

        output.loc = main;
        output.dir = (wm->ball.pos.loc - Field::ourGoalCenter).dir().radian();
    }
    else
    {
        output.loc = Field::ourGoalCenter;
    }

    return output;

}

Position Play::goalieInPenalty()
{
    Position out;
    out.loc = Field::ourGoalCenter;

    QList<int> nearestOpp = wm->kn->findNearestOppositeTo(Field::ourPenaltySpot);

    if( nearestOpp.size() > 0)
    {
        Ray2D oppDir(wm->oppRobot[nearestOpp.at(0)].pos.loc, AngleDeg::rad2deg(wm->oppRobot[nearestOpp.at(0)].pos.dir));
        Line2D ourGoalLine(Field::ourGoalPost_L, Field::ourGoalPost_R);
        Segment2D ourGoalMargin(Vector2D(Field::ourGoalPost_L.x, Field::ourGoalPost_L.y+500), Vector2D(Field::ourGoalPost_R.x, Field::ourGoalPost_R.y-500));
        Segment2D ourGoal(Field::ourGoalPost_L, Field::ourGoalPost_R);
        Vector2D intersect = oppDir.intersection(ourGoalLine);
        if( ourGoalMargin.contains(intersect) )
        {
            if( ourGoal.contains(intersect))
                out.loc = (Field::ourGoalCenter*2 + intersect)/3;
            else
            {
                double dist2Left = (intersect - Field::ourGoalPost_L).length();
                double dist2Right = (intersect - Field::ourGoalPost_R).length();

                if( dist2Left < dist2Right )
                    out.loc = (Field::ourGoalCenter*2 + Field::ourGoalPost_L)/3;
                else
                    out.loc = (Field::ourGoalCenter*2 + Field::ourGoalPost_R)/3;
            }
        }
    }

    return out;

}
//===========================================================================================
void Play::Deffence_Geometry_making()
{

    double Deffence_Rad = Field::goalCircleDEF_R;
    Vector2D B2GC=(Field::ourGoalCenter-wm->ball.pos.loc);
    double Dist_Ball_2_Goal=B2GC.length();//wm->ball.pos.loc-Field::ourGoalCenter).length();

    if(Dist_Ball_2_Goal>Deffence_Rad) Dist_2_Deffence=Dist_Ball_2_Goal-Deffence_Rad;
    else Dist_2_Deffence=-100;

    Vector2D B2LG=(Field::ourGoalPost_L - wm->ball.pos.loc);
    Vector2D B2RG=(Field::ourGoalPost_R - wm->ball.pos.loc);
    double ang = (B2RG.dir().radian()-B2LG.dir().radian());

    Vector2D B2DC=B2GC; // Defining Ball 2 Center Of Deffence
    B2DC.setLength(Dist_2_Deffence);
    Deffence_center=wm->ball.pos.loc+B2DC;
    Wall_length=2*Dist_2_Deffence*tan(ang/2); // length of Deffence Wall which fully protected goal
    Wall=B2GC;
    Wall.setLength(Wall_length); Wall.rotate(90);
}
//===========================================================================================
bool Play::Find_OppRobot_BallOwner()
{
    int ans=-1,num=0;
    double mindist=100000000;
    for(int jj=0;jj<PLAYERS_MAX_NUM;jj++)
    {
        if(wm->oppRobot[jj].isValid==false) continue;
        double dist=(wm->oppRobot[jj].pos.loc-wm->ball.pos.loc).length();
        if(dist<400) num++;
        if(dist<mindist)
        {
            mindist=dist;
            ans=jj;
        }
    }
    if(ans!=-1 && num<2 && mindist < 250) // Just One Player Can Own The Ball
    {
        BallOwner_Finded=true;
        //        qDebug() << " Opponent Robot Number Has Owned The Ball: " << ans ;
        Player1 = wm->oppRobot[ans].pos;
        return true;
    }

    else
    {
        return false;
    }

}
//===========================================================================================
bool Play::Find_Pass_Receiver(Position Player1)
{
    bool finded=false;
    //    Ray2D R2T(Player1.loc,AngleDeg::deg2rad(Player1.dir)); // Robot To Target
    double P1_Dir=Player1.dir,min_Diff_ang=100;
    int ans=-1;//,num=0;
    Vector2D P1_P2 = Vector2D(0,0);
    for(int jj=0;jj<PLAYERS_MAX_NUM;jj++)
    {
        if(!wm->oppRobot[jj].isValid) continue;
        P1_P2 = (wm->oppRobot[jj].pos.loc - Player1.loc);
        if(P1_P2.length2()<90000) continue; // Dont Consider Ball Owner & Near Robots
        double Dif_ang;
        Dif_ang = (P1_P2.dir().radian()-P1_Dir);
        if(Dif_ang > M_PI) Dif_ang -= 2*M_PI;
        else if(Dif_ang < -M_PI) Dif_ang += 2*M_PI;
        Dif_ang=abs(Dif_ang);
        if(Dif_ang<min_Diff_ang)
        {
            min_Diff_ang=Dif_ang;
            ans=jj;
        }
    }
    if(min_Diff_ang > AngleDeg::deg2rad(20) || wm->ball.vel.loc.length() > 0.4 )
    {
//        qDebug() << "!! Check The Pass Reciever !! ";
        return false ;
        //        ans=0; // Please Do Not Force To Close
    }

    else
    {
        //        qDebug() << " Opponent Robot " << ans << " Will Get Pass ! " ;
        Player2 = wm->oppRobot[ans].pos ;
        finded = true ;
    }
    return finded;//wm->oppRobot[ans].pos;
}
//===========================================================================================
bool Play::Find_AnyOther_Opp_Dangerous()
{
    //    bool finded=false;
    //    double min_d = 35000000,min_a = 100;
    int min_i = -1;
    //    Vector2D predictedPos;
    double BallVell_Dir = wm->ball.vel.loc.dir().radian();
    double min_Diff_ang=100;
    if( wm->ball.isValid && wm->ball.vel.loc.length() > 0.5)
    {
        Vector2D B_P2 = Vector2D(0,0);
        for(int jj=0;jj<PLAYERS_MAX_NUM;jj++)
        {
            if(!wm->oppRobot[jj].isValid) continue;
            B_P2 = (wm->oppRobot[jj].pos.loc - wm->ball.pos.loc);
            double Dif_ang;
            Dif_ang = (B_P2.dir().radian()-BallVell_Dir);
            if(Dif_ang > M_PI) Dif_ang -= 2*M_PI;
            else if(Dif_ang < -M_PI) Dif_ang += 2*M_PI;
            Dif_ang=abs(Dif_ang);
            if(Dif_ang<min_Diff_ang)
            {
                min_Diff_ang=Dif_ang;
                min_i = jj;
            }
        }

        if(min_Diff_ang > AngleDeg::deg2rad(30) || wm->ball.vel.loc.length() < 0.4 )
        {
            //            qDebug() << "!! Check Any Other Dangerous !! ";
            return false ;
        }
        else
        {
            Player2 = wm->oppRobot[min_i].pos;
            //            qDebug() << " Player # " << min_i << " Is Dangerous " ;
            return true;
        }
    }
    else return false;

}
//===========================================================================================
Vector2D Play::Find_MostDangerous_Goal_Point()
{
    QList<int> our;
    QList<int> ourAgents = wm->kn->ActiveAgents();

    for(int i=0;i<ourAgents.size();i++)
    {
        switch (wm->ourRobot[ourAgents.at(i)].Role)
        {
        case AgentRole::DefenderLeft:
            our.append(ourAgents.at(i));
            break;
        case AgentRole::DefenderRight:
            our.append(ourAgents.at(i));
            break;
        default:
            break;
        }
    }

    tANDp out;
    out.prob = 0;

    QList<tANDp> TANDPis;
    int prob=100;
    //    QList<int> our = this->findOurObstacles();
    for(int jj=-7;jj<8;jj++)
    {
        Vector2D Point;
        Point.x = Field::ourGoalCenter.x;
        Point.y = Field::ourGoalCenter.y + jj*(Field::ourGoalPost_L.y/10);
        tANDp tp;
        tp.pos=Point;
        int min_prob = 100;
        for(int ii=0;ii<our.size();ii++)
        {
            if(wm->ourRobot[our.at(ii)].isValid)
            {
                if(true)//wm->ourRobot[our.at(ii)].pos.loc.x < wm.x)
                {
                    Segment2D ball2Point(wm->ball.pos.loc,Point);
                    double dist2R = ball2Point.dist(wm->ourRobot[our.at(ii)].pos.loc);
                    if (dist2R < 600 ) prob = dist2R/6.0;
                    else prob = 100;
                    if(prob < min_prob) min_prob = prob;
                }
            }
            /*if(abs(jj) > 7) */min_prob = min_prob-abs(jj);//*((7.0-abs(jj))/3.0);
            if(min_prob < 0) min_prob = 0 ;
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
    return out.pos;
}
//===========================================================================================
int Play::Find_Dyno_Deffence(int Left_ID, int Right_ID, Vector2D Deff_center)
{
    if((wm->ourRobot[Left_ID].pos.loc-Deff_center).length2() < (wm->ourRobot[Right_ID].pos.loc-Deff_center).length2())
        return Left_ID;
    else return Right_ID;

}
//===========================================================================================
Vector2D Play::Find_Deff_center(Vector2D loc)
{
    double Dist_2_Deffence_loc;
    Vector2D Deffence_center_loc;
    double Deffence_Rad=Field::goalCircleDEF_R;
    Vector2D L2GC=(Field::ourGoalCenter-loc);
    double Dist_Loc_2_Goal=L2GC.length();//wm->ball.pos.loc-Field::ourGoalCenter).length();

    if(Dist_Loc_2_Goal > Deffence_Rad) Dist_2_Deffence_loc = Dist_Loc_2_Goal-Deffence_Rad;
    else Dist_2_Deffence_loc = -100;

    Vector2D L2DC=L2GC; // Defining Ball 2 Center Of Deffence
    L2DC.setLength(Dist_2_Deffence_loc);
    Deffence_center_loc = loc + L2DC;
    return Deffence_center_loc;
}
//===========================================================================================
Vector2D Play::Average_Positioning(Vector2D l1, Vector2D l2)
{
    Vector2D V1 = l1 - Field::ourGoalCenter ;
    Vector2D V2 = l2 - Field::ourGoalCenter ;
    double D_ang = (V1.dir().radian()-V2.dir().radian());
    if(D_ang > M_PI) D_ang-=2*M_PI;
    else if(D_ang < -M_PI) D_ang+=2*M_PI;
    Vector2D Average;
    Average = V2.rotate(AngleDeg::rad2deg(D_ang/2));
    Average = Field::ourGoalCenter + Average ;
    return Average;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void Play::addseg()
//{

//    segList.clear(); // SO IMPORTANT !!!
//    for(int i=0;i<32;i++)
//    {

//        Segment2D seg(leftspot,rightspot);
//        segList.push_back(seg);
//        //qDebug()<<"segorigin"<<segList.at(i).origin().x;
//        leftspot.x=leftspot.x+25;
//        rightspot.x=rightspot.x+25;
//    }

//}


//===========================================================================================
//===========================================================================================
//===========================================================================================
