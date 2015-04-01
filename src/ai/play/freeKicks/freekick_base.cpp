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
}

Tactic *freeKick_base::getTactic(int id)
{
    if(id >= PLAYERS_MAX_NUM || id < 0) return NULL;
    return tactics[id];
}

void freeKick_base::zonePositions(int leftID, int RightID, int MidID, Position &goalie, Position &left, bool& leftNav, Position &right, bool& rightNav)
{
    goalie.loc = Field::ourGoalCenter;

    if( wm->cmgs.theirPenaltyKick() )
    {
        right.loc = Field::oppPenaltyParallelLineCenter;
        right.loc.y = Field::oppPenaltyParallelLineCenter.y - (Field::MaxY*0.5);
        rightNav = false;

        left.loc.x = Field::oppPenaltyParallelLineCenter.x;
        left.loc.y = Field::oppPenaltyParallelLineCenter.y + (Field::MaxY*0.5);
        leftNav = false;
    }
    else if( wm->kn->IsInsideGolieArea(wm->ball.pos.loc) && (!wm->cmgs.canKickBall()) )
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
        Vector2D secondPointForGoalie;

        bool need2newPoints = false;

        BallOwner_Finded = Find_OppRobot_BallOwner();
        if(BallOwner_Finded) Player_filter(Player1);
        Deffence_Geometry_making();

        Ball_IS_Toward_Goal = Ball_Toward_Goal();
        bool Two_Deffence=true;
        if(MidID!=-1) Two_Deffence=false;

        if(!Ball_IS_Toward_Goal)
        {
            leftNav = true; rightNav = true;
            if(Two_Deffence) // Two Deffences Are Available
            {
                secondPointForGoalie = ( wm->ourRobot[leftID].pos.loc + wm->ourRobot[RightID].pos.loc)/2;
                need2newPoints = !hasPositionForGoalie(secondPointForGoalie);
                if(!BallOwner_Finded) // NIST dar ekhtiare kesi  >> Ref2b(ball)
                {
                    bool Is_AnyOther_Dangerous = false ;
                    Is_AnyOther_Dangerous = Find_AnyOther_Opp_Dangerous();
                    if(Is_AnyOther_Dangerous)
                    {
                        // Player1 Is Ready To Give A Pass To Player2

                        Vector2D Dyno_right,Dyno_left,Deff_center;
                        //                        bool Is_left;
                        //                        Ref_2Deff_Player2(Player2,Left2,Right2,Deff_center);
                        Deff_center = Find_Deff_center(Player2.loc);
                        int Dyno_Id = Find_Dyno_Deffence(leftID,RightID,Deff_center);
                        //                        Ref_1Deff_Player2(Player2,leftID,RightID,Dyno_Id,Loc);
                        Ref_2Deff_Player(Player1);

                        if(Dyno_Id == leftID)// && Is_Player2_Dangerous) // left Deffence Must Go
                        {
                            Ref_1Deff_Loc(Player2.loc,leftID,RightID,Dyno_Id,Dyno_left);
                            Left_loc = Average_Positioning(Left_loc , Dyno_left);
                        }
                        else
                        {
                            Ref_1Deff_Loc(Player2.loc,leftID,RightID,Dyno_Id,Dyno_right);
                            Right_loc = Average_Positioning(Dyno_right , Right_loc);
                        }
                    }
                    else Ref_2Deff_Ball(); // !!!!! Will Complete
                }
                else //(BallOwner_Finded)
                {
                    bool Is_Danger_Player=false;
                    Is_Danger_Player = Danger_Player_Direction(Player1,150);
                    if(Is_Danger_Player) Ref_2Deff_Player(Player1);
                    else // The Ball Owner Player Is Not Toward Our Goal
                    {
                        bool Is_anyone_recieve_pass = Find_Pass_Receiver(Player1);
                        if(Is_anyone_recieve_pass)
                        {
                            // Player1 Is Ready To Give A Pass To Player2

                            Vector2D Dyno_right,Dyno_left,Deff_center;
                            //                        bool Is_left;
                            //                        Ref_2Deff_Player2(Player2,Left2,Right2,Deff_center);
                            Deff_center = Find_Deff_center(Player2.loc);
                            int Dyno_Id = Find_Dyno_Deffence(leftID,RightID,Deff_center);
                            //                        Ref_1Deff_Player2(Player2,leftID,RightID,Dyno_Id,Loc);
                            Ref_2Deff_Player(Player1);

                            if(Dyno_Id == leftID)// && Is_Player2_Dangerous) // left Deffence Must Go
                            {
                                Ref_1Deff_Loc(Player2.loc,leftID,RightID,Dyno_Id,Dyno_left);
                                Left_loc = Average_Positioning(Left_loc , Dyno_left);
                            }
                            else
                            {
                                Ref_1Deff_Loc(Player2.loc,leftID,RightID,Dyno_Id,Dyno_right);
                                Right_loc = Average_Positioning(Dyno_right , Right_loc);
                            }
                        }
                        else // No One Recieve Pass
                        {
                            Ref_2Deff_Ball();
                        }
                    }
                    //                Ref_2Deff_Player(Player1);
                }
            }
            else // One Deffence !
            {
                secondPointForGoalie = Find_MostDangerous_Goal_Point();

                if(!BallOwner_Finded) // NIST dar ekhtiare kesi  >> Ref2b(ball)
                {
                    Ref_1Deff_Ball(leftID,RightID,MidID);
                }
                else //(BallOwner_Finded)
                {
                    Ref_1Deff_Player(Player1,leftID,RightID,MidID);
                }
                // For Let The Second Deffence Come Back
                if(MidID==RightID) Ref_1Deff_Loc(wm->ball.pos.loc,leftID,RightID,leftID,Left_loc);
                else if(MidID==leftID) Ref_1Deff_Loc(wm->ball.pos.loc,leftID,RightID,RightID,Right_loc);
            }
            //            Goalie_loc = Find_MostDangerous_Goal_Point();
            //            qDebug() << " Goalie : ( " << Goalie_loc.x << "," << Goalie_loc.y << ")";
            //            goalie.loc = Danger_point ;
        }
        else // Ball Is Moving To Our Goal
        {
            Line2D L2R(Vector2D(Field::ourGoalCenter.x,Field::MaxY),Vector2D(Field::ourGoalCenter.x,Field::MinY));
            Line2D BV2T(wm->ball.pos.loc,AngleDeg::rad2deg(wm->ball.vel.loc.dir().radian())); //Ball Vell 2 Target
            Vector2D intersect_Point = L2R.intersection(BV2T);

            secondPointForGoalie = intersect_Point;

            rightNav = false; leftNav = false;
            if(Two_Deffence) Ref_2Deff_Moving_Ball();
            else Ref_1Deff_Moving_Ball(leftID,RightID,MidID);
        }

        //        Ref_2Deff_Moving_Ball();
        //                Goalie_loc.y = (Field::ourGoalCenter.y + 2*Goalie_loc.y)/3; //
        //                Goalie_loc.x += 200;
        //                goalie.loc = Goalie_loc ;
        left.loc = Left_loc;
        left.dir = (wm->ourRobot[leftID].pos.loc - Field::ourGoalPost_L).dir().radian();
        right.loc = Right_loc;
        right.dir = (wm->ourRobot[RightID].pos.loc - Field::ourGoalPost_R).dir().radian();

        if( (left.loc-wm->ball.pos.loc).length() < 400)
            leftNav = false;
        if( (right.loc-wm->ball.pos.loc).length() < 400)
            rightNav = false;

        //Goal Keeper Positions
        //        qDebug()<<"secondPointForGoalie : "<<secondPointForGoalie.x<<" , "<<secondPointForGoalie.y;
        if( need2newPoints )
            secondPointForGoalie = (right.loc + left.loc)/2;

        goalie = goaliePosition(secondPointForGoalie);

        //        qDebug() <<"Left Deffence " << left.loc.x << "," << left.loc.y ;
        //        qDebug() <<"Right Deffence " << right.loc.x << "," << right.loc.y ;
    }
}

//===========================================================================================
//===========================================================================================
void freeKick_base::Player_filter(Position Player)
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
void freeKick_base::Ref_2Deff_Player(Position p)
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
            Left_loc.setLength(Wall_length/3);
            if(Dist_2_Deffence<700) Left_loc.setLength(90) ;
            Left_loc = Deffence_center-Left_loc;
            Right_loc = Wall;
            Right_loc.setLength(Wall_length/3);
            if(Dist_2_Deffence<700) Right_loc.setLength(90) ;
            Right_loc = Deffence_center+Right_loc;
        }
    }
    else Ref_2Deff_Ball();

}
//===========================================================================================
void freeKick_base::Ref_2Deff_Ball()
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
void freeKick_base::Ref_2Deff_Player2(Position p, Vector2D &Left_2, Vector2D &Right_2, Vector2D &Deff_center)
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
void freeKick_base::Ref_2Deff_Moving_Ball()
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
void freeKick_base::Ref_1Deff_Player(Position p,int Left_ID,int Right_ID,int Mid_ID)
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
void freeKick_base::Ref_1Deff_Ball(int Left_ID, int Right_ID, int Mid_ID)
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
void freeKick_base::Ref_1Deff_Player2(Position p, int Left_ID, int Right_ID, int Mid_ID, Vector2D &Loc)
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
void freeKick_base::Ref_1Deff_Moving_Ball(int Left_ID,int Right_ID,int Mid_ID)
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
void freeKick_base::Ref_2Deff_Loc(Vector2D loc) // ball2goal >> loc2goal
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
void freeKick_base::Ref_1Deff_Loc(Vector2D loc, int Left_ID, int Right_ID, int Mid_ID, Vector2D &Loc)
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
bool freeKick_base::Danger_Player_Direction(Position p, int thr)
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
        qDebug() << " !! CHECK Danger Player !! " ;
    }

    return is_dangerous;
}
//===========================================================================================
bool freeKick_base::Ball_Toward_Goal()
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

bool freeKick_base::hasPositionForGoalie(Vector2D midOfDef)
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

Position freeKick_base::goaliePosition(Vector2D midOfDef)
{
    Position output;

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
        output.dir = (-midOfDef + wm->ball.pos.loc).dir().radian();
    }
    else
    {
        output.loc = Field::ourGoalCenter;
    }

    return output;

}
//===========================================================================================
void freeKick_base::Deffence_Geometry_making()
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
bool freeKick_base::Find_OppRobot_BallOwner()
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
bool freeKick_base::Find_Pass_Receiver(Position Player1)
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
bool freeKick_base::Find_AnyOther_Opp_Dangerous()
{
    //    bool finded=false;
    //    double min_d = 35000000,min_a = 100;
    int min_i = -1;
    //    Vector2D predictedPos;
    double BallVell_Dir = wm->ball.vel.loc.dir().radian();
    double min_Diff_ang=100;
    if( wm->ball.isValid && wm->ball.vel.loc.length() > 0.8)
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

        if(min_Diff_ang > AngleDeg::deg2rad(20) || wm->ball.vel.loc.length() < 0.4 )
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
Vector2D freeKick_base::Find_MostDangerous_Goal_Point()
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
int freeKick_base::Find_Dyno_Deffence(int Left_ID, int Right_ID, Vector2D Deff_center)
{
    if((wm->ourRobot[Left_ID].pos.loc-Deff_center).length2() < (wm->ourRobot[Right_ID].pos.loc-Deff_center).length2())
        return Left_ID;
    else return Right_ID;

}
//===========================================================================================
Vector2D freeKick_base::Find_Deff_center(Vector2D loc)
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
Vector2D freeKick_base::Average_Positioning(Vector2D l1, Vector2D l2)
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

//===========================================================================================
//===========================================================================================
//===========================================================================================

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
