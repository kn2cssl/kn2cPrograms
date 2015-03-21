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

void Play::zonePositions(int leftID, int RightID, int MidID, Position &goalie, Position &left, Position &right)
{
    goalie.loc = Vector2D(Field::MinX,0);

    if( wm->cmgs.theirPenaltyKick() )
    {
        //        center.loc = Field::oppPenaltyParallelLineCenter;

        right.loc = Field::oppPenaltyParallelLineCenter;
        right.loc.y = Field::oppPenaltyParallelLineCenter.y - (Field::MaxY*0.5);

        left.loc.x = Field::oppPenaltyParallelLineCenter.x;
        left.loc.y = Field::oppPenaltyParallelLineCenter.y + (Field::MaxY*0.5);
    }
    else if( wm->kn->IsInsideGolieArea(wm->ball.pos.loc) && (!wm->cmgs.canKickBall()) )
    {
        right.loc.x = Field::ourGoalCenter.x + 800;
        right.loc.y = Field::ourGoalCenter.y - 350;

        left.loc.x = Field::ourGoalCenter.x + 800;
        left.loc.y = Field::ourGoalCenter.y + 350;
    }
    else
    {
        //        qDebug() << "LEFT ID : " << leftID << ", Mid ID : " << MidID <<", RIGHT ID : " << RightID ;
        BallOwner_Finded = Find_OppRobot_BallOwner();
        if(BallOwner_Finded) Player_filter(Player1);
        Deffence_Geometry_making();
        bool Ball_IS_Toward_Goal;
        Ball_IS_Toward_Goal = Ball_Toward_Goal();
        bool Two_Deffence=true;
        if(MidID!=-1) Two_Deffence=false;
        if(Two_Deffence) // Two Deffences Are Available
        {
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
                        // Find Any Other Dangerous Player
                        if(true)
                        {
                            Ref_2Deff_Ball();
                        }

                    }
                }
                //                Ref_2Deff_Player(Player1);
            }
        }
        else // One Deffence !
        {
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

        left.loc = Left_loc;
        right.loc = Right_loc;
        left.dir =(wm->ourRobot[leftID].pos.loc - Field::ourGoalPost_L).dir().radian();
        right.dir=(wm->ourRobot[RightID].pos.loc - Field::ourGoalPost_R).dir().radian();
        //        qDebug() <<"Left Deffence " << left.loc.x << "," << left.loc.y ;
        //        qDebug() <<"Right Deffence " << right.loc.x << "," << right.loc.y ;
    }
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
    Segment2D LG2RG(Field::ourGoalPost_L,Field::ourGoalPost_R); // Left Goal to Right Goal
    Line2D L2R(Vector2D(Field::ourGoalCenter.x,FIELD_MAX_Y),Vector2D(Field::ourGoalCenter.x,-FIELD_MAX_Y));
    Line2D B2OT(wm->ball.pos.loc,AngleDeg::rad2deg(p.dir)); //Ball to Opponent Target
    Vector2D intersect_Point = L2R.intersection(B2OT);
    //    qDebug() << "Intersect Point" << intersect_Point.x << " , " << intersect_Point.y;
    //    qDebug() << Field::ourGoalPost_R.y << " , " << Field::ourGoalPost_L.y ;
    if((intersect_Point.y > Field::ourGoalPost_R.y-100) && (intersect_Point.y < Field::ourGoalPost_L.y+100))
    {
        if(p.dir < -M_PI/2 || p.dir > M_PI/2)
        {
            Vector2D B2DC = Deffence_center - wm->ball.pos.loc;
            double Rot_ang = (p.dir - B2DC.dir().radian());
            if(Rot_ang>M_PI) Rot_ang-=2*M_PI;
            else if(Rot_ang<-M_PI) Rot_ang+=2*M_PI;

            B2DC.rotate(AngleDeg::rad2deg(Rot_ang*0.8));
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
    Line2D L2R(Vector2D(Field::ourGoalCenter.x,FIELD_MAX_Y),Vector2D(Field::ourGoalCenter.x,-FIELD_MAX_Y));
    Line2D P2OT(p.loc,AngleDeg::rad2deg(p.dir)); //Player to Opponent Target
    Vector2D intersect_Point = L2R.intersection(P2OT);
    //    qDebug() << "Intersect Point" << intersect_Point.x << " , " << intersect_Point.y;
    //    qDebug() << Field::ourGoalPost_R.y << " , " << Field::ourGoalPost_L.y ;
    if((intersect_Point.y > Field::ourGoalPost_R.y-100) && (intersect_Point.y < Field::ourGoalPost_L.y+100))
    {
        if(p.dir < -M_PI/2 || p.dir > M_PI/2)
        {
            // --------  Defining New Deffence Center ---------------
            double Deffence_Rad=1100;
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
void Play::Ref_1Deff_Player(Position p,int Left_ID,int Right_ID,int Mid_ID)
{
    //    Segment2D LG2RG(Field::ourGoalPost_L,Field::ourGoalPost_R); // Left Goal to Right Goal
    Line2D L2R(Vector2D(Field::ourGoalCenter.x,FIELD_MAX_Y),Vector2D(Field::ourGoalCenter.x,-FIELD_MAX_Y));
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
        qDebug() << "!!!!!!! No Point For Deffence Selected !!!!!!! " ;
        Left_loc =Vector2D(0,0);
        Right_loc=Vector2D(0,0);
    }

}
//===========================================================================================
void Play::Ref_1Deff_Player2(Position p, int Left_ID, int Right_ID, int Mid_ID, Vector2D &Loc)
{

    //    Segment2D LG2RG(Field::ourGoalPost_L,Field::ourGoalPost_R); // Left Goal to Right Goal
    Line2D L2R(Vector2D(Field::ourGoalCenter.x,FIELD_MAX_Y),Vector2D(Field::ourGoalCenter.x,-FIELD_MAX_Y));
    Line2D P2OT(p.loc,AngleDeg::rad2deg(p.dir)); //Ball to Opponent Target
    Vector2D intersect_Point = L2R.intersection(P2OT);
    //    qDebug() << "Intersect Point" << intersect_Point.x << " , " << intersect_Point.y;
    //    qDebug() << Field::ourGoalPost_R.y << " , " << Field::ourGoalPost_L.y ;
    if(intersect_Point.y < Field::ourGoalPost_R.y-100) intersect_Point.y = Field::ourGoalPost_R.y-100;
    else if(intersect_Point.y > Field::ourGoalPost_L.y+100) intersect_Point.y = Field::ourGoalPost_L.y+100;
    if(p.dir < -M_PI/2 || p.dir > M_PI/2)
    {

        double Deffence_Rad=1100;
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
void Play::Ref_2Deff_Loc(Vector2D loc) // ball2goal >> loc2goal
{
    double Dist_2_Deffence_loc,Wall_length_Loc;
    Vector2D Deffence_center_loc,Wall_Loc;
    double Deffence_Rad=1100;
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
    double Deffence_Rad=1100;
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
    Line2D L2R(Vector2D(Field::ourGoalCenter.x,FIELD_MAX_Y),Vector2D(Field::ourGoalCenter.x,-FIELD_MAX_Y));
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
bool Play::Ball_Toward_Goal()
{
    bool To_Goal=false;
    if(wm->ball.vel.loc.length()>0.4)
    {

        Vector2D Intersect_Point;
        //    Segment2D LG2RG(Field::ourGoalPost_L,Field::ourGoalPost_R); // Left Goal to Right Goal
        Line2D L2R(Vector2D(Field::ourGoalCenter.x,FIELD_MAX_Y),Vector2D(Field::ourGoalCenter.x,-FIELD_MAX_Y));
        Line2D B2T(wm->ball.pos.loc,AngleDeg::rad2deg(wm->ball.vel.dir)); //Ball to Target
        Intersect_Point = L2R.intersection(B2T);
        if((Intersect_Point.y > Field::ourGoalPost_R.y-150) && (Intersect_Point.y < Field::ourGoalPost_L.y+150))
        {
            //            qDebug() << " OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOy !!";
            if(wm->ball.vel.dir < -M_PI/2 || wm->ball.vel.dir > M_PI/2)
            {

                To_Goal = true;
                qDebug() << " Ball Is Moving Toward Goal" ;
            }
        }
    }
    return To_Goal;
}
//===========================================================================================
void Play::Deffence_Geometry_making()
{

    double Deffence_Rad=1100;
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
        qDebug() << "!! Check The Pass Reciever !! ";
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
        //        for(int i=0;i<PLAYERS_MAX_NUM;i++)
        //        {
        //            if(!wm->oppRobot[i].isValid) continue;
        //            predictedPos = wm->kn->PredictDestination(wm->oppRobot[i].pos.loc, wm->ball.pos.loc,wm->opp_vel,wm->ball.vel.loc);
        //            double distance = (predictedPos - wm->oppRobot[i].pos.loc).length();

        //            if( distance < min_d )
        //            {
        //                min_d = distance;
        //                min_i = i;
        //            }

        //        }

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


        //    Position p2 = wm->oppRobot[min_i].pos;

        //    double Ball2Player = (p2.loc - wm->ball.pos.loc).dir().radian();
        //    double diff_ang=BallVell_Dir - Ball2Player;
        //    if(diff_ang > M_PI) diff_ang-=2*M_PI;
        //    else if(diff_ang < -M_PI) diff_ang+=2*M_PI;
        //    diff_ang = fabs(diff_ang);
        //    qDebug() << " Check Any Other Dangerous ! ";
        //    if(min_d < 4000 && (diff_ang < AngleDeg::deg2rad(20)))
        qDebug() << " Min_Diff_ang : " << AngleDeg::rad2deg(min_Diff_ang);
        if(min_Diff_ang > AngleDeg::deg2rad(20) || wm->ball.vel.loc.length() < 0.4 )
        {
            qDebug() << "!! Check Any Other Dangerous !! ";
            return false ;
        }
        else
        {
            Player2 = wm->oppRobot[min_i].pos;
            qDebug() << " Player # " << min_i << " Is Dangerous " ;
            return true;
        }
    }
    else return false;

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
    double Deffence_Rad=1100;
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


//===========================================================================================
//===========================================================================================
//===========================================================================================
