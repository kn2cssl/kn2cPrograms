#include "freekick_base.h"

freeKick_base::freeKick_base(WorldModel *worldmodel, QObject *parent)
{
    rolesIsInit = false;
    wm = worldmodel;
    for(int i=0; i<PLAYERS_MAX_NUM; i++)
        tactics[i] = NULL;

    freeKickStart = false;

    tGolie = new TacticGoalie(wm);

    tDefenderLeft = new TacticDefender(wm);
    tDefenderRight = new TacticDefender(wm);

    tAttackerLeft = new TacticAttacker(wm);
    tAttackerMid = new TacticAttacker(wm);
    tAttackerRight = new TacticAttacker(wm);

    defenderflag=false;
    defendersflag=false;
    angelflag=false;
    angelflags=false;
    defendermovmentflag=true;
    goalkeepermovmentflag=true;

    previousLeftID = -1;
    previousRightID = -1;
}

Tactic *freeKick_base::getTactic(int id)
{
    if(id >= PLAYERS_MAX_NUM || id < 0) return NULL;
    return tactics[id];
}

void freeKick_base::zonePositions(int leftID, int RightID, int MidID, Position &goalie, Position &left, bool& leftNav, Position &right, bool& rightNav)
{
    goalie.loc = Field::ourGoalCenter;

    if( wm->kn->IsInsideGolieArea(wm->ball.pos.loc) && (!wm->cmgs.canKickBall()) )
    {
        right.loc.x = Field::ourGoalCenter.x + Field::goalCircle_R + 200;
        right.loc.y = Field::ourGoalCenter.y - 350;
        rightNav = true;

        left.loc.x = Field::ourGoalCenter.x + Field::goalCircle_R + 200;
        left.loc.y = Field::ourGoalCenter.y + 350;
        leftNav = true;
    }
    else
    {
        leftNav=true;
        rightNav=true;

        if( leftID != -1 )
            left = wm->ourRobot[leftID].pos;
        if( RightID != -1 )
            right = wm->ourRobot[RightID].pos;

        //variables:

        Vector2D Midpos;
        double Midangel;


        //defence with two players: goalkeeper : defender flag=false
        Vector2D leftspot={-4200,Field::ourGoalPost_L.y+350};//-4300=Field::ourGoalPostL.x+300
        Vector2D rightspot={-4200,Field::ourGoalPost_R.y-350};//-4300=Field::ourGoalPostR.x+300

        Vector2D ballpos=wm->ball.pos.loc;
        if(wm->ball.pos.loc.x<Field::MinX+20)
        {
            ballpos.y=wm->ball.pos.loc.y;
            ballpos.x=Field::MinX+20;
        }

        Vector2D ball2ourGoalPostLvec=Field::ourGoalPost_L-ballpos;
        Vector2D ball2ourGoalPostRvec=Field::ourGoalPost_R-ballpos;
        Segment2D goalline(Field::ourGoalPost_R,Field::ourGoalPost_L);
        Segment2D goalkeeperline(leftspot,rightspot);
        Segment2D ourGoaPostR2OurRightCorner(Field::ourGoalPost_R,Field::bottomLeftCorner);
        Segment2D ourGoaPostL2OurLeftCorner(Field::ourGoalPost_L,Field::upperLeftCorner);
        Segment2D ourwidthline(Field::bottomLeftCorner,Field::upperLeftCorner);


        Line2D *ball2ourGoalPostR=new Line2D(ballpos,Field::ourGoalPost_R);
        Line2D *ball2ourGoalPostL= new Line2D(ballpos,Field::ourGoalPost_L);
        Line2D *ball2ourGoalCenter=new Line2D(ballpos,Field::ourGoalCenter);

        float lowPassFilterFactor=0.2*2;
        ballVelAngel=((wm->ball.vel.loc.dir().degree()-ballVelAngel)*lowPassFilterFactor)+ballVelAngel;
        Line2D *ball2goal = new Line2D(ballpos,ballVelAngel);
        //        Line2D *ball2goal = new Line2D(ballpos,wm->ball.vel.loc.dir().degree());

        Vector2D ball2ourGoalCentervec=Field::ourGoalCenter-ballpos;


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


        Circle2D dangerousarea(Field::ourGoalCenter,Field::goalCircle_R+500);//goalCircle_R=1000;

        //    if(oppIds.size()>0)
        //    {
        //        for(int i=0;i<oppIds.size();i++)
        //        {
        //            if((wm->oppRobot[oppIds.at(i)].pos.loc-Field::ourGoalCenter).length()<1250+ROBOT_RADIUS && (wm->oppRobot[oppIds.at(i)].pos.loc-Field::ourGoalCenter).length()>1000 )
        //            {
        //                qDebug()<<"dangeres//////////////////////////////////////////////////////////";
        //                dangerousarea.assign(Field::ourGoalCenter,Field::goalCircle_R+100);
        //                break;
        //            }
        //        }
        //    }
        ////////////////////////////////////////////////////////////for changing the goalkeeper pos according to the pos of defenders..

        //    leftspot={-4300,-500};
        //    rightspot={-4300,500};

        ////////////////////////////////////////////////////////////


        Vector2D goallineintersection;//Intersection between  Line 2D from ball in direction of attacker and goallineSeg
        Vector2D goalkeeperlineintersection;//Intersection between  Line 2D from ball in direction of attacker and goalkeeperlineSeg
        Vector2D goal;//will be used as a temperory variable

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
                        if(goalkeeperline.existIntersection(*attacker2goalline))//the attacker is locating out of margine...
                        {
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
                                temp.setLength(ROBOT_RADIUS+20+20+20+20);
                                goal=ball2ourGoalPostRintersection+temp;

                                Line2D *test = new Line2D(goal,ball2ourGoalPostRvec.dir().degree());//for checking if the Vector temp have to be added itself or with 180 rotation

                                if(!(goalline.existIntersection(*test)))
                                {
                                    goal=ball2ourGoalPostRintersection-temp;
                                }
                            }
                            else if(!rightside && leftside)
                            {
                                Vector2D ball2ourGoalPostLintersection=blocker.intersection(*ball2ourGoalPostL);
                                Vector2D temp=goalkeeperline2goalline.rotatedVector(90);
                                temp.setLength(ROBOT_RADIUS+20+20+20+20);
                                goal=ball2ourGoalPostLintersection+temp;

                                Line2D *test=new Line2D(goal,ball2ourGoalPostLvec.dir().degree());//for checking if the Vector temp have to be added itself or with 180 rotation

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
                        }


                        else
                        {
                            if((ballpos-Field::ourGoalPost_L).length2()>(ballpos-Field::ourGoalPost_R).length2())
                            {
                                goalie.loc.y=Field::ourGoalPost_R.y-80;
                                goalie.loc.x=Field::ourGoalPost_R.x+200;//=-3025+robotradius+65
                            }

                            else
                            {
                                goalie.loc.y=Field::ourGoalPost_L.y+80;
                                goalie.loc.x=Field::ourGoalPost_L.x+200;
                            }
                        }

                        goalie.dir=wm->oppRobot[oppIds.at(0)].pos.dir+M_PI;//in the opposite of the attacker...
                    }

                    ////////////////////////////////////////////////////////////for changing the goalkeeper pos according to the pos of defenders..
                    //                        else if(ourGoaPostR2OurRightCorner.existIntersection(*attacker2goalline))
                    //                        {
                    //                            qDebug()<<"right";
                    //                            Vector2D intersection=goalkeeperline.intersection(*ball2ourGoalPostR);

                    //                            Vector2D temp=ball2ourGoalPostRvec.rotatedVector(90);
                    //                            temp.setLength(ROBOT_RADIUS+20+20+20+20);

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
                    //                            temp.setLength(ROBOT_RADIUS+20+20+20+20);

                    //                            goal=intersection+temp;

                    //                            Line2D *test=new Line2D(goal,ball2ourGoalPostLvec.dir().degree());

                    //                            if(!(goalline.existIntersection(*test)))
                    //                            {
                    //                                goal=intersection-temp;
                    //                            }

                    //                            goalie.loc=goal;
                    //                            goalie.dir=(ball2ourGoalPostLvec.dir().radian()+M_PI);
                    //                        }


                    else
                    {
                        if(goalkeeperline.existIntersection(*ball2ourGoalCenter))
                        {
                            Vector2D ball2goalkeeperlineintersection=goalkeeperline.intersection(*ball2ourGoalCenter);
                            goalie.loc=ball2goalkeeperlineintersection;
                        }
                        else
                        {
                            if((ballpos-Field::ourGoalPost_L).length2()>(ballpos-Field::ourGoalPost_R).length2())
                            {
                                goalie.loc.y=Field::ourGoalPost_R.y-80;
                                goalie.loc.x=Field::ourGoalPost_R.x+200;
                            }

                            else
                            {
                                goalie.loc.y=Field::ourGoalPost_L.y+80;
                                goalie.loc.x=Field::ourGoalPost_L.x+200;
                            }
                        }
                        goalie.dir=ball2ourGoalCentervec.dir().radian()+M_PI;//in the opposite of the attacker...
                    }
                }
                else//defa saro shekl gerefte...
                {
                    if(wm->ball.pos.loc.y<-middleAreaWidth || wm->ball.pos.loc.y>middleAreaWidth)
                    {

                        if(!angelflag)
                        {
                            if((ballpos-Field::ourGoalPost_L).length2()>(ballpos-Field::ourGoalPost_R).length2())
                            {
                                Vector2D intersection=goalkeeperline.intersection(*ball2ourGoalCenter);

                                Vector2D temp=ball2ourGoalCentervec.rotatedVector(90);
                                temp.setLength(ROBOT_RADIUS+20+20);

                                goal=intersection+temp;

                                Line2D *test=new Line2D(goal,ball2ourGoalCentervec.dir().degree());

                                Vector2D goalLinetestLineIntersection=goalline.intersection(*test);

                                if(  !((goalLinetestLineIntersection-Field::ourGoalPost_L).length2()<(goalLinetestLineIntersection-Field::ourGoalPost_R).length2())  )//the defender is locating in the wrong pos
                                {
                                    goal=intersection-temp;
                                }
                                goalie.loc=goal;
                                goalie.dir=(ball2ourGoalCentervec.dir().radian()+M_PI);
                            }
                            else
                            {
                                Vector2D intersection=goalkeeperline.intersection(*ball2ourGoalCenter);

                                Vector2D temp=ball2ourGoalCentervec.rotatedVector(90);
                                temp.setLength(ROBOT_RADIUS+20+20);

                                goal=intersection+temp;

                                Line2D *test=new Line2D(goal,ball2ourGoalCentervec.dir().degree());

                                Vector2D goalLinetestLineIntersection=goalline.intersection(*test);

                                if(  !((goalLinetestLineIntersection-Field::ourGoalPost_L).length2()>(goalLinetestLineIntersection-Field::ourGoalPost_R).length2())  )//the defender is locating in the wrong pos
                                {
                                    goal=intersection-temp;
                                }
                                goalie.loc=goal;
                                goalie.dir=(ball2ourGoalCentervec.dir().radian()+M_PI);
                            }
                        }
                        else
                        {
                            goalie.loc=Field::ourGoalCenter;
                            goalie.dir=(ball2ourGoalCentervec.dir().radian()+M_PI);
                        }

                        goalkeepermovmentflag=true;
                    }
                    else
                    {
                        if(goalkeepermovmentflag && wm->ball.isValid)
                        {
                            if((ballpos-Field::ourGoalPost_L).length2()>(ballpos-Field::ourGoalPost_R).length2() )
                            {
                                //                                Vector2D intersection=goalkeeperline.intersection(*ball2ourGoalPostL);

                                //                                Vector2D temp=ball2ourGoalPostLvec.rotatedVector(90);
                                //                                temp.setLength(ROBOT_RADIUS+20+20+20+20);

                                //                                goal=intersection+temp;

                                //                                Line2D *test=new Line2D(goal,ball2ourGoalPostLvec.dir().degree());

                                //                                if(!(goalline.existIntersection(*test)))
                                //                                {
                                //                                    goal=intersection-temp;
                                //                                }

                                //                                goalkeeperlastpos=goal;
                                //                                goalkeeperlastdir=(ball2ourGoalPostLvec.dir().radian()+M_PI);
                                goalkeeperlasttirak=leftTirak;
                            }
                            else
                            {
                                //                                Vector2D intersection;
                                //                                intersection=goalkeeperline.intersection(*ball2ourGoalPostR);

                                //                                Vector2D temp=ball2ourGoalPostRvec.rotatedVector(90);
                                //                                temp.setLength(ROBOT_RADIUS+20+20+20+20);

                                //                                goal=intersection+temp;

                                //                                Line2D *test=new Line2D(goal,ball2ourGoalPostRvec.dir().degree());

                                //                                if(!(goalline.existIntersection(*test)))
                                //                                {
                                //                                    goal=intersection-temp;
                                //                                }
                                //                                goalkeeperlastpos=goal;
                                //                                goalkeeperlastdir=(ball2ourGoalPostRvec.dir().radian()+M_PI);


                                goalkeeperlasttirak=rightTirak;
                            }

                            goalkeepermovmentflag=false;


                        }

                        if(goalkeeperlasttirak==leftTirak)
                        {
                            Vector2D intersection=goalkeeperline.intersection(*ball2ourGoalCenter);

                            Vector2D temp=ball2ourGoalCentervec.rotatedVector(90);
                            temp.setLength(ROBOT_RADIUS+20+20);

                            goal=intersection+temp;

                            Line2D *test=new Line2D(goal,ball2ourGoalCentervec.dir().degree());

                            Vector2D goalLinetestLineIntersection=goalline.intersection(*test);

                            if(  !((goalLinetestLineIntersection-Field::ourGoalPost_L).length2()<(goalLinetestLineIntersection-Field::ourGoalPost_R).length2())  )//the defender is locating in the wrong pos
                            {
                                goal=intersection-temp;
                            }
                            goalie.dir=(ball2ourGoalCentervec.dir().radian()+M_PI);

                        }

                        if(goalkeeperlasttirak==rightTirak)
                        {
                            Vector2D intersection=goalkeeperline.intersection(*ball2ourGoalCenter);

                            Vector2D temp=ball2ourGoalCentervec.rotatedVector(90);
                            temp.setLength(ROBOT_RADIUS+20+20);

                            goal=intersection+temp;

                            Line2D *test=new Line2D(goal,ball2ourGoalCentervec.dir().degree());

                            Vector2D goalLinetestLineIntersection=goalline.intersection(*test);

                            if(  !((goalLinetestLineIntersection-Field::ourGoalPost_L).length2()>(goalLinetestLineIntersection-Field::ourGoalPost_R).length2())  )//the defender is locating in the wrong pos
                            {
                                goal=intersection-temp;
                            }
                            goalie.dir=(ball2ourGoalCentervec.dir().radian()+M_PI);
                        }

                        goalie.loc=goal;
                        //                        goalie.loc=goalkeeperlastpos;
                        //                        goalie.dir=goalkeeperlastdir;
                    }
                }
            }

            //defender:
            {
                angelflag=false;//if the ball is loacating in the special margine the angel falg will switch to true below...
                if(wm->ball.pos.loc.y<-middleAreaWidth || wm->ball.pos.loc.y>middleAreaWidth)
                {
                    if((ballpos-Field::ourGoalPost_L).length2()<(ballpos-Field::ourGoalPost_R).length2())
                    {
                        Vector2D temp1,temp2,intersection;
                        dangerousarea.intersection(*ball2ourGoalCenter,&temp1,&temp2);//the intersection between the line from ball to nearer tirack and the defined circle...

                        if(wm->kn->IsInsideField(temp1))
                        {
                            intersection=temp1;
                        }
                        else
                        {
                            intersection=temp2;
                        }

                        Vector2D temp=ball2ourGoalCentervec.rotatedVector(90);
                        temp.setLength(ROBOT_RADIUS+20+20);

                        goal=intersection+temp;

                        Line2D *test=new Line2D(goal,ball2ourGoalCentervec.dir().degree());

                        Vector2D goalLinetestLineIntersection=goalline.intersection(*test);

                        if(  !((goalLinetestLineIntersection-Field::ourGoalPost_L).length2()<(goalLinetestLineIntersection-Field::ourGoalPost_R).length2())  )//the defender is locating in the wrong pos
                        {
                            goal=intersection-temp;
                        }

                        Midpos=goal;
                        Midangel=(ball2ourGoalCentervec.dir().radian()+M_PI);
                        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////dar inn halat dige halate momase bar tirakha laghv shode chon ye defa ke dar rahe balltoourgalcenter bashe kafye va goaler mire vasate darvaze
                        if(ourGoaPostL2OurLeftCorner.dist(ballpos)<1000 && ourGoaPostL2OurLeftCorner.dist(ballpos)>100)
                        {
                            dangerousarea.intersection(*ball2ourGoalCenter,&temp1,&temp2);//the intersection between the line from ball to nearer tirack and the defined circle...
                            if(wm->kn->IsInsideField(temp1))
                            {
                                intersection=temp1;
                            }
                            else
                            {
                                intersection=temp2;
                            }

                            Midpos=intersection;
                            angelflag=true;
                        }

                        if(ourGoaPostL2OurLeftCorner.dist(ballpos)<100)//it happens when the ball is near the our width line
                        {
                            Midpos.x=Field::ourGoalCenter.x+(2*ROBOT_RADIUS-50);//momase bar khate arzi
                            Midpos.y=Field::ourGoalCenter.y+1200;
                            angelflag=true;
                        }

                        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    }
                    else
                    {
                        Vector2D temp1,temp2,intersection;
                        dangerousarea.intersection(*ball2ourGoalCenter,&temp1,&temp2);//the intersection between the line from ball to nearer tirack and the defined circle...

                        if(wm->kn->IsInsideField(temp1))
                        {
                            intersection=temp1;
                        }
                        else
                        {
                            intersection=temp2;
                        }

                        Vector2D temp=ball2ourGoalCentervec.rotatedVector(90);
                        temp.setLength(ROBOT_RADIUS+20+20);

                        goal=intersection+temp;

                        Line2D *test=new Line2D(goal,ball2ourGoalCentervec.dir().degree());

                        Vector2D goalLinetestLineIntersection=goalline.intersection(*test);

                        if(  !((goalLinetestLineIntersection-Field::ourGoalPost_L).length2()>(goalLinetestLineIntersection-Field::ourGoalPost_R).length2())  )//the defender is locating in the wrong pos
                        {
                            goal=intersection-temp;
                        }

                        Midpos=goal;
                        Midangel=(ball2ourGoalCentervec.dir().radian()+M_PI);
                        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////dar inn halat dige halate momase bar tirakha laghv shode chon ye defa ke dar rahe balltoourgalcenter bashe kafye va goaler mire vasate darvaze
                        if(ourGoaPostR2OurRightCorner.dist(ballpos)<1000 && ourGoaPostR2OurRightCorner.dist(ballpos)>100)
                        {
                            dangerousarea.intersection(*ball2ourGoalCenter,&temp1,&temp2);//the intersection between the line from ball to nearer tirack and the defined circle...

                            if(wm->kn->IsInsideField(temp1))
                            {
                                intersection=temp1;
                            }
                            else
                            {
                                intersection=temp2;
                            }

                            Midpos=intersection;
                            angelflag=true;
                        }

                        if(ourGoaPostR2OurRightCorner.dist(ballpos)<100)//it happens when the ball is near the our width line
                        {
                            Midpos.x=Field::ourGoalCenter.x+(2*ROBOT_RADIUS-50);
                            Midpos.y=Field::ourGoalCenter.y-1200;
                            angelflag=true;
                        }

                        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    }

                    defendermovmentflag=true;
                }
                else
                {
                    if(defendermovmentflag  && wm->ball.isValid)
                    {
                        if((ballpos-Field::ourGoalPost_L).length2()<(ballpos-Field::ourGoalPost_R).length2())
                        {
                            //                            Vector2D temp1,temp2,intersection;
                            //                            dangerousarea.intersection(*ball2ourGoalPostL,&temp1,&temp2);//the intersection between the line from ball to nearer tirack and the defined circle...

                            //                            if(wm->kn->IsInsideField(temp1))
                            //                            {
                            //                                intersection=temp1;
                            //                            }
                            //                            else
                            //                            {
                            //                                intersection=temp2;
                            //                            }

                            //                            Vector2D temp=ball2ourGoalPostLvec.rotatedVector(90);
                            //                            temp.setLength(ROBOT_RADIUS+20+20+20);

                            //                            goal=intersection+temp;

                            //                            Line2D *test=new Line2D(goal,ball2ourGoalPostLvec.dir().degree());

                            //                            if(!(goalline.existIntersection(*test)))//the defender is locating in the wrong pos
                            //                            {
                            //                                goal=intersection-temp;
                            //                            }

                            //                            defenderlastpos=goal;
                            //                            defenderlastdir=(ball2ourGoalPostLvec.dir().radian()+M_PI);

                            defenderlasttirak=leftTirak;
                        }

                        else
                        {
                            //                            Vector2D temp1,temp2,intersection;
                            //                            dangerousarea.intersection(*ball2ourGoalPostR,&temp1,&temp2);//the intersection between the line from ball to nearer tirack and the defined circle...

                            //                            if(wm->kn->IsInsideField(temp1))
                            //                            {
                            //                                intersection=temp1;
                            //                            }
                            //                            else
                            //                            {
                            //                                intersection=temp2;
                            //                            }

                            //                            Vector2D temp=ball2ourGoalPostRvec.rotatedVector(90);
                            //                            temp.setLength(ROBOT_RADIUS+20+20+20);

                            //                            goal=intersection+temp;

                            //                            Line2D *test=new Line2D(goal,ball2ourGoalPostRvec.dir().degree());

                            //                            if(!(goalline.existIntersection(*test)))//the defender is locating in the wrong pos
                            //                            {
                            //                                goal=intersection-temp;
                            //                            }

                            //                            defenderlastpos=goal;
                            //                            defenderlastdir=(ball2ourGoalPostRvec.dir().radian()+M_PI);

                            defenderlasttirak=rightTirak;
                        }

                        defendermovmentflag=false;

                    }

                    if(defenderlasttirak==leftTirak)
                    {
                        Vector2D temp1,temp2,intersection;
                        dangerousarea.intersection(*ball2ourGoalCenter,&temp1,&temp2);//the intersection between the line from ball to nearer tirack and the defined circle...

                        if(wm->kn->IsInsideField(temp1))
                        {
                            intersection=temp1;
                        }
                        else
                        {
                            intersection=temp2;
                        }

                        Vector2D temp=ball2ourGoalCentervec.rotatedVector(90);
                        temp.setLength(ROBOT_RADIUS+20+20);

                        goal=intersection+temp;

                        Line2D *test=new Line2D(goal,ball2ourGoalCentervec.dir().degree());

                        Vector2D goalLinetestLineIntersection=goalline.intersection(*test);

                        if(  !((goalLinetestLineIntersection-Field::ourGoalPost_L).length2()<(goalLinetestLineIntersection-Field::ourGoalPost_R).length2())  )//the defender is locating in the wrong pos
                        {
                            goal=intersection-temp;
                        }

                        Midangel=(ball2ourGoalCentervec.dir().radian()+M_PI);
                        Midpos=goal;

                    }

                    if(defenderlasttirak==rightTirak)
                    {
                        Vector2D temp1,temp2,intersection;
                        dangerousarea.intersection(*ball2ourGoalCenter,&temp1,&temp2);//the intersection between the line from ball to nearer tirack and the defined circle...

                        if(wm->kn->IsInsideField(temp1))
                        {
                            intersection=temp1;
                        }
                        else
                        {
                            intersection=temp2;
                        }

                        Vector2D temp=ball2ourGoalCentervec.rotatedVector(90);
                        temp.setLength(ROBOT_RADIUS+20+20);

                        goal=intersection+temp;

                        Line2D *test=new Line2D(goal,ball2ourGoalCentervec.dir().degree());

                        Vector2D goalLinetestLineIntersection=goalline.intersection(*test);

                        if(  !((goalLinetestLineIntersection-Field::ourGoalPost_L).length2()>(goalLinetestLineIntersection-Field::ourGoalPost_R).length2())  )//the defender is locating in the wrong pos
                        {
                            goal=intersection-temp;
                        }

                        Midpos=goal;
                        Midangel=(ball2ourGoalCentervec.dir().radian()+M_PI);
                        //                    Midpos=defenderlastpos;
                        //                    Midangel=defenderlastdir;

                    }

                }
                if((ballpos-Field::ourGoalCenter).length()<1500-ROBOT_RADIUS)//zamani ke tooop poshte modafe gharar migirad
                {
                    if(wm->kn->IsInsideGolieArea(wm->ball.pos.loc))//zamani ke toooop dar mohavate ast....
                    {
                        Vector2D intersection,temp1,temp2;
                        dangerousarea.intersection(*ball2ourGoalCenter,&temp1,&temp2);//the intersection between the line from ball to nearer tirack and the defined circle...
                        if(wm->kn->IsInsideField(temp1))
                        {
                            intersection=temp1;
                        }
                        else
                        {
                            intersection=temp2;
                        }

                        Midpos=intersection;
                        Midangel=(ball2ourGoalCentervec.dir().radian()+M_PI);
                    }

                    else
                    {
                        if(oppIsInField)
                        {
                            Vector2D ball2nearestattacker=(wm->oppRobot[oppIds.at(0)].pos.loc-wm->ball.pos.loc);
                            ball2nearestattacker.setLength(200+200);
                            if((ballpos-wm->oppRobot[oppIds.at(0)].pos.loc).length()<200)
                            {
                                ball2nearestattacker.setLength(ROBOT_RADIUS+20);
                            }
                            Midpos=ballpos+ball2nearestattacker;
                            Midangel=ball2nearestattacker.dir().radian();
                            leftNav=false;
                            rightNav=false;
                        }

                    }
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

                ///////////////////////////////////////////////////////////////////////////////////////check the sitution if the ball is closing to our goal...(change all the setpoints according to the situtation that the ball is closing to our goal)
                if( goalline.existIntersection(*ball2goal)  &&  wm->ball.vel.loc.length()>0.2)
                {
                    //defender:
                    Vector2D temp1,temp2,ball2goaldangerousareaintersection,ball2goalgoalkeeperlineintersection,ball2goalgoallineintersection;

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
                    if(goalkeeperline.existIntersection(*ball2goal))
                    {
                        ball2goalgoalkeeperlineintersection=goalkeeperline.intersection(*ball2goal);
                        goalie.loc=ball2goalgoalkeeperlineintersection;
                        goalie.dir=wm->ball.vel.loc.dir().radian()+M_PI;
                    }
                    else
                    {
                        ball2goalgoallineintersection=goalline.intersection(*ball2goal);
                        goalie.loc=ball2goalgoallineintersection;
                        goalie.dir=wm->ball.vel.loc.dir().radian()+M_PI;
                    }
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
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else//defence with three player()
        {
            //goalkeeper:
            {
                if(!defendersflag)//defa saro shekl nagerefte....
                {
                    //                    qDebug()<<"defenderflag=false";
                    float attacker2balldistance;
                    if(oppIds.size()>0)
                    {
                        attacker2balldistance=((wm->oppRobot[oppIds.at(0)].pos.loc-ballpos)).length();
                    }

                    if(attacker2balldistance<attackernoticeabledistance  && oppIsInField  &&  goalline.existIntersection(*attacker2goalline))//the attacker wants to attack to safegoalline not goalline...//goalline.existIntersection(*attacker2goalline)
                    {
                        if(goalkeeperline.existIntersection(*attacker2goalline))//the attacker is locating out of margine...
                        {
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
                                temp.setLength(ROBOT_RADIUS+20+20+20+20);
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
                                temp.setLength(ROBOT_RADIUS+20+20+20+20);
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
                        }
                        else
                        {
                            if((ballpos-Field::ourGoalPost_L).length2()>(ballpos-Field::ourGoalPost_R).length2())
                            {
                                goalie.loc.y=Field::ourGoalPost_R.y-80;
                                goalie.loc.x=Field::ourGoalPost_R.x+200;
                            }

                            else
                            {
                                goalie.loc.y=Field::ourGoalPost_L.y+80;
                                goalie.loc.x=Field::ourGoalPost_L.x+200;
                            }
                        }

                        goalie.dir=wm->oppRobot[oppIds.at(0)].pos.dir+M_PI;//in the opposite of the attacker...
                    }

                    ////////////////////////////////////////////////////////////for changing the goalkeeper pos according to the pos of defenders..
                    //                        else if(ourGoaPostR2OurRightCorner.existIntersection(*attacker2goalline))
                    //                        {
                    //                            qDebug()<<"right";
                    //                            Vector2D intersection=goalkeeperline.intersection(*ball2ourGoalPostR);

                    //                            Vector2D temp=ball2ourGoalPostRvec.rotatedVector(90);
                    //                            temp.setLength(ROBOT_RADIUS+20+20+20+20);

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
                    //                            temp.setLength(ROBOT_RADIUS+20+20+20+20);

                    //                            goal=intersection+temp;

                    //                            Line2D *test=new Line2D(goal,ball2ourGoalPostLvec.dir().degree());

                    //                            if(!(goalline.existIntersection(*test)))
                    //                            {
                    //                                goal=intersection-temp;
                    //                            }

                    //                            goalie.loc=goal;
                    //                            goalie.dir=(ball2ourGoalPostLvec.dir().radian()+M_PI);
                    //                        }


                    else
                    {
                        if(goalkeeperline.existIntersection(*ball2ourGoalCenter))
                        {
                            Vector2D ball2goalkeeperlineintersection=goalkeeperline.intersection(*ball2ourGoalCenter);
                            goalie.loc=ball2goalkeeperlineintersection;
                        }
                        else
                        {
                            if((ballpos-Field::ourGoalPost_L).length2()>(ballpos-Field::ourGoalPost_R).length2())
                            {
                                goalie.loc.y=Field::ourGoalPost_R.y-80;
                                goalie.loc.x=Field::ourGoalPost_R.x+200;
                            }
                            else
                            {
                                goalie.loc.y=Field::ourGoalPost_L.y+80;
                                goalie.loc.x=Field::ourGoalPost_L.x+200;
                            }
                        }
                        goalie.dir=ball2ourGoalCentervec.dir().radian()+M_PI;//in the opposite of the attacker...
                    }
                }
                else//defa saro shekl garefte...
                {
                    //                    qDebug()<<"defenderflag=true";
                    if(!angelflags)//toop dar noghteye koor nist...
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
                            temp.setLength((2*ROBOT_RADIUS)+20);//radius of robot
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
                            temp.setLength((2*ROBOT_RADIUS)+20);//radius of robot
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
                        //                    temp.setLength(ROBOT_RADIUS+20);
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

                        Vector2D goal2ballpos=ballpos-goal;
                        goalie.loc=goal;
                        goalie.dir=goal2ballpos.dir().radian();
                    }

                    else//tooop dar noghteye kooor ast va ye modafe baraye bastan kollle darvaze kafye...
                    {
                        goalie.loc=Field::ourGoalCenter;
                        goalie.dir=(ball2ourGoalCentervec.dir().radian()+M_PI);
                    }
                }
            }

            //defenders:
            {
                Vector2D temp1,temp2,intersection;
                Vector2D Leftgoal;
                Vector2D Rightgoal;

                if(ourwidthline.dist(ballpos)>1000)//kharej az noghteye kooor...har modafe ye tirak...
                {
                    angelflags=false;
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
                        temp.setLength(ROBOT_RADIUS+20);

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
                        temp.setLength(ROBOT_RADIUS+20);


                        Rightgoal=intersection+temp;


                        Line2D *test=new Line2D(Rightgoal,ball2ourGoalPostRvec.dir().degree());

                        if(!(goalline.existIntersection(*test)))//the defender is locating in the wrong pos
                        {
                            Rightgoal=intersection-temp;
                        }
                        right.loc=Rightgoal;
                        right.dir=(ball2ourGoalPostRvec.dir().radian()+M_PI);
                    }

                }
                else//toop dar noghteye kooor ast....
                {
                    angelflags=true;
                    if((ballpos-Field::ourGoalPost_L).length2()<(ballpos-Field::ourGoalPost_R).length2())//modafe chap bayad zavyeye baste ra bebandad va modafe ras bere sare kare jadid
                    {
                        if(ourGoaPostL2OurLeftCorner.dist(ballpos)>100)
                        {
                            dangerousarea.intersection(*ball2ourGoalCenter,&temp1,&temp2);//the intersection between the line from ball to our goal center
                            if(wm->kn->IsInsideField(temp1))
                            {
                                intersection=temp1;
                            }
                            else
                            {
                                intersection=temp2;
                            }

                            Leftgoal=intersection;
                        }

                        else
                        {
                            Leftgoal.x=Field::ourGoalCenter.x+(2*ROBOT_RADIUS-50);//momase bar khate arzi
                            Leftgoal.y=Field::ourGoalCenter.y+1200;
                        }

                        Rightgoal.y=Field::ourGoalCenter.y;
                        Rightgoal.x=Field::ourGoalCenter.x+1200;
                    }

                    else
                    {
                        if(ourGoaPostR2OurRightCorner.dist(ballpos)>100)
                        {
                            dangerousarea.intersection(*ball2ourGoalCenter,&temp1,&temp2);//the intersection between the line from ball to our goal center
                            if(wm->kn->IsInsideField(temp1))
                            {
                                intersection=temp1;
                            }
                            else
                            {
                                intersection=temp2;
                            }

                            Rightgoal=intersection;
                        }

                        else
                        {
                            Rightgoal.x=Field::ourGoalCenter.x+(2*ROBOT_RADIUS-50);//momase bar khate arzi
                            Rightgoal.y=Field::ourGoalCenter.y-1200;
                            //angelflag=true;
                        }

                        Leftgoal.y=Field::ourGoalCenter.y;
                        Leftgoal.x=Field::ourGoalCenter.x+1200;
                    }

                    left.loc=Leftgoal;
                    right.loc=Rightgoal;
                    left.dir=ball2ourGoalCentervec.dir().radian()+M_PI;
                    right.dir=ball2ourGoalCentervec.dir().radian()+M_PI;
                }
                if((ballpos-Field::ourGoalCenter).length()<1500-ROBOT_RADIUS)//zamani ke tooop poshte modafe gharar migirad
                {
                    if(wm->kn->IsInsideGolieArea(wm->ball.pos.loc))//zamani ke toooop dar mohavate ast....
                    {
                        Vector2D intersection,temp1,temp2;
                        dangerousarea.intersection(*ball2ourGoalCenter,&temp1,&temp2);//the intersection between the line from ball to nearer tirack and the defined circle...

                        if(wm->kn->IsInsideField(temp1))
                        {
                            intersection=temp1;
                        }
                        else
                        {
                            intersection=temp2;
                        }

                        if((ballpos-Field::ourGoalPost_L).length2()<(ballpos-Field::ourGoalPost_R).length2())
                        {
                            left.loc=intersection;
                            left.dir=ball2ourGoalCentervec.dir().radian()+M_PI;
                            right.loc={Field::ourGoalCenter.x+1200,Field::ourGoalCenter.y};
                            right.dir=0;
                        }
                        else
                        {
                            right.loc=intersection;
                            right.dir=ball2ourGoalCentervec.dir().radian()+M_PI;
                            left.loc={Field::ourGoalCenter.x+1200,Field::ourGoalCenter.y};
                            left.dir=0;
                        }
                    }
                    else
                    {
                        if(oppIsInField)
                        {
                            if((ballpos-Field::ourGoalPost_L).length2()<(ballpos-Field::ourGoalPost_R).length2())
                            {
                                leftNav=false;
                                Vector2D ball2nearestattacker=(wm->oppRobot[oppIds.at(0)].pos.loc-wm->ball.pos.loc);
                                ball2nearestattacker.setLength(200+200);
                                if((ballpos-wm->oppRobot[oppIds.at(0)].pos.loc).length()<200)
                                {
                                    ball2nearestattacker.setLength(ROBOT_RADIUS+20);
                                }

                                left.loc=ballpos+ball2nearestattacker;
                                left.dir=ball2nearestattacker.dir().radian();
                                right.loc={Field::ourGoalCenter.x+1200,Field::ourGoalCenter.y};
                                right.dir=0;
                            }
                            else
                            {
                                rightNav=false;
                                Vector2D ball2nearestattacker=(wm->oppRobot[oppIds.at(0)].pos.loc-wm->ball.pos.loc);
                                ball2nearestattacker.setLength(200+200);

                                if((ballpos-wm->oppRobot[oppIds.at(0)].pos.loc).length()<200)
                                {
                                    ball2nearestattacker.setLength(ROBOT_RADIUS+20);
                                }

                                right.loc=ballpos+ball2nearestattacker;
                                right.dir=ball2nearestattacker.dir().radian();
                                left.loc={Field::ourGoalCenter.x+1200,Field::ourGoalCenter.y};
                                left.dir=0;
                            }
                        }

                    }
                }

                ////////////////////////////////////////////////////////////////////////////////
                if(((wm->ourRobot[leftID].pos.loc)-Leftgoal).length()<desiredleftdefenderdistance && ((wm->ourRobot[RightID].pos.loc)-Rightgoal).length()<desiredrightdefenderdistance)
                {
                    defendersflag=true;
                }
                else
                {
                    defendersflag=false;
                }


                /////////////////////////////////////////////////////////////////////////////vaqti setpointha dar ham gharar migirand
                if((Leftgoal-Rightgoal).length()<2*ROBOT_RADIUS)
                {
                    //goalkeeper:
                    goalie.loc=Field::ourGoalCenter;
                    goalie.dir=ball2ourGoalCentervec.dir().radian()+M_PI;

                    //defenders:
                    Vector2D temp1,temp2,dangerousareaball2ourGoalCenterlineintersection;

                    dangerousarea.intersection(*ball2ourGoalCenter,&temp1,&temp2);
                    if(wm->kn->IsInsideField(temp1))
                    {
                        dangerousareaball2ourGoalCenterlineintersection=temp1;
                    }
                    else
                    {
                        dangerousareaball2ourGoalCenterlineintersection=temp2;
                    }

                    Vector2D temp=ball2ourGoalCentervec.rotatedVector(90);
                    temp.setLength(ROBOT_RADIUS+20+20);
                    temp1=dangerousareaball2ourGoalCenterlineintersection+temp;
                    temp2= dangerousareaball2ourGoalCenterlineintersection-temp;
                    if((Field::ourGoalPost_L-temp2).length2()<(Field::ourGoalPost_L-temp1).length2())
                    {
                        left.loc=temp2;
                        right.loc=temp1;
                    }
                    else
                    {
                        left.loc=temp1;
                        right.loc=temp2;
                    }
                }

                ///////////////////////////////////////////////////////////////////////////////////////check the sitution if the ball is closing to our goal...
                if(goalline.existIntersection(*ball2goal)  &&  wm->ball.vel.loc.length()>0.5)
                {
                    //goalkeeper:
                    if(goalkeeperline.existIntersection(*ball2goal))
                    {
                        Vector2D ball2goalgoalkeeperlineintersection=goalkeeperline.intersection(*ball2goal);
                        goalie.loc=ball2goalgoalkeeperlineintersection;
                    }
                    else
                    {
                        Vector2D ball2goalgoallineintersection=goalline.intersection(*ball2goal);
                        goalie.loc=ball2goalgoallineintersection;
                    }

                    goalie.dir=wm->ball.vel.loc.dir().radian()+M_PI;
                }

            }
        }
    }

}

bool freeKick_base::haltedRobotIsInField(int robotID)
{
    if( robotID != -1 )
    {
        if( wm->ourRobot[robotID].isValid )
            return true;
    }

    return false;
}

void freeKick_base::initRole()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();
    activeAgents.removeOne(wm->ref_goalie_our);
    wm->ourRobot[wm->ref_goalie_our].Role = AgentRole::Golie;

    int freeKickerID = wm->freeKickerID;

    if( wm->ourRobot[freeKickerID].isValid )
    {
        switch (activeAgents.length()) {
        case 1:
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            break;
        case 2:
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
            break;
        case 3:
            wm->ourRobot[freeKickerID].Role = AgentRole::AttackerMid;
            activeAgents.removeOne(freeKickerID);

            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
            break;
        case 4:
            wm->ourRobot[freeKickerID].Role = AgentRole::AttackerMid;
            activeAgents.removeOne(freeKickerID);

            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerLeft;
            break;
        case 5:
            wm->ourRobot[freeKickerID].Role = AgentRole::AttackerMid;
            activeAgents.removeOne(freeKickerID);

            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerLeft;
            break;
        }
    }
    else
    {
        switch (activeAgents.length()) {
        case 1:
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            break;
        case 2:
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
            break;
        case 3:
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
            break;
        case 4:
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerLeft;
            break;
        case 5:
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerLeft;
            break;
        }

    }

    rolesIsInit = true;
    freeKickStart = false;
}

void freeKick_base::setTactics(int index)
{
    switch (wm->ourRobot[index].Role) {
    case AgentRole::Golie:
        tactics[index] = tGolie;
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
    case AgentRole::AttackerRight:
        tactics[index] = tAttackerRight;
        break;
    case AgentRole::AttackerLeft:
        tactics[index] = tAttackerLeft;
        break;
    default:
        break;
    }
}
