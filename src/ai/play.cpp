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
        qDebug() << "LEFT ID : " << leftID << ", Mid ID : " << MidID <<", RIGHT ID : " << RightID ;
        Player1 = Find_OppRobot_BallOwner();
        if(BallOwner_Finded) Player_filter(Player1);
        Deffence_Geometry_making();

        if(MidID==-1) // Two Deffences Are Available
        {
            if(!BallOwner_Finded) // NIST dar ekhtiare kesi  >> Ref2b(ball)
            {
                Ref_2Deff_Ball();

                bool Danger_Player;
                Danger_Player_Direction(Player1,Danger_Player);
                if(Danger_Player) Ref_2Deff_Player(Player1);
                else // The Ball Owner Player Is Not Toward Our Goal
                {

                }
            }

            else //(BallOwner_Finded)
            {

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
        }


        //        if(wm->ourRobot[leftID].isValid)//MidID==-1)
        //        {
        //            if(!BallOwner_Finded)// NIST dar ekhtiare kesi  >> Ref2b(ball)
        //                Ref_2Deff_Ball();

        //            else if(BallOwner_Finded)
        //                Ref_2Deff_Player(Player1);


        //        }
        //        if(!wm->ourRobot[leftID].isValid)//MidID!=-1)
        //        {
        //            if(!BallOwner_Finded)
        //            {
        //                Ref_1Deff_Ball(leftID,RightID,RightID);//mid Id
        //                //                qDebug() << "RIGHT        ID : " << RightID;
        //            }
        //            else if(BallOwner_Finded)
        //            {
        //                Ref_1Deff_Player(Player1,leftID,RightID,RightID);// Mid Id
        //                //                qDebug() << "Right ID : " << RightID ;
        //            }
        //        }

        Ref_1Deff_Loc(wm->oppRobot[4].pos.loc,leftID,RightID,RightID);
        //        qDebug() << "Left ID " << leftID;
        //        qDebug() << Left_loc.x;
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
        if(Player1.dir < -M_PI/2 || Player1.dir > M_PI/2)
        {
            //            qDebug() << " Opponent Robot Is Dangerous ! ";
            Vector2D B2DC = Deffence_center - wm->ball.pos.loc;
            double Rot_ang = (Player1.dir - B2DC.dir().radian());
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

void Play::Ref_1Deff_Player(Position p,int Left_ID,int Right_ID,int Mid_ID)
{
    Segment2D LG2RG(Field::ourGoalPost_L,Field::ourGoalPost_R); // Left Goal to Right Goal
    Line2D L2R(Vector2D(Field::ourGoalCenter.x,FIELD_MAX_Y),Vector2D(Field::ourGoalCenter.x,-FIELD_MAX_Y));
    Line2D B2OT(wm->ball.pos.loc,AngleDeg::rad2deg(p.dir)); //Ball to Opponent Target
    Vector2D intersect_Point = L2R.intersection(B2OT);
    //    qDebug() << "Intersect Point" << intersect_Point.x << " , " << intersect_Point.y;
    //    qDebug() << Field::ourGoalPost_R.y << " , " << Field::ourGoalPost_L.y ;
    if(intersect_Point.y < Field::ourGoalPost_R.y-100) intersect_Point.y = Field::ourGoalPost_R.y-100;
    else if(intersect_Point.y > Field::ourGoalPost_L.y+100) intersect_Point.y = Field::ourGoalPost_L.y+100;
    if(Player1.dir < -M_PI/2 || Player1.dir > M_PI/2)
    {
        //            qDebug() << " Opponent Robot Is Dangerous ! ";
        Vector2D B2DC = Deffence_center - wm->ball.pos.loc;
        double Rot_ang = (Player1.dir - B2DC.dir().radian());
        if(Rot_ang>M_PI) Rot_ang-=2*M_PI;
        else if(Rot_ang<-M_PI) Rot_ang+=2*M_PI;

        B2DC.rotate(AngleDeg::rad2deg(Rot_ang*0.75));
        Deffence_center = wm->ball.pos.loc + B2DC ;

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
        //        }
    }
    //    else Ref_1Deff_Ball();
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

void Play::Ref_1Deff_Loc(Vector2D loc, int Left_ID, int Right_ID, int Mid_ID)
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
        Left_loc = Wall_Loc;
        Left_loc.setLength((Wall_length_Loc/4));
        if(Dist_2_Deffence_loc<700) Left_loc.setLength(90) ;
        Left_loc = Deffence_center_loc-Left_loc;
        //        qDebug() << "left : " << Left_loc.x;
    }
    else if(Mid_ID==Right_ID)
    {
        Right_loc = Wall_Loc;
        Right_loc.setLength((Wall_length_Loc/4));
        if(Dist_2_Deffence_loc<700) Right_loc.setLength(90) ;
        Right_loc = Deffence_center_loc+Right_loc;
    }
    else
    {
        qDebug() << "!!!!!!! No Point For Deffence Selected !!!!!!! " ;
        Left_loc =Vector2D(0,0);
        Right_loc=Vector2D(0,0);
    }


}

//===========================================================================================

void Play::Danger_Player_Direction(Position p, bool &Dangerous)
{
    Vector2D Intersect_Point;
    //    Segment2D LG2RG(Field::ourGoalPost_L,Field::ourGoalPost_R); // Left Goal to Right Goal
    Line2D L2R(Vector2D(Field::ourGoalCenter.x,FIELD_MAX_Y),Vector2D(Field::ourGoalCenter.x,-FIELD_MAX_Y));
    Line2D B2OT(wm->ball.pos.loc,AngleDeg::rad2deg(p.dir)); //Ball to Opponent Target
    Intersect_Point = L2R.intersection(B2OT);
    if((Intersect_Point.y > Field::ourGoalPost_R.y-100) && (Intersect_Point.y < Field::ourGoalPost_L.y+100))
    {
        if(p.dir < -M_PI/2 || p.dir > M_PI/2)
        {
            Dangerous = true;
        }
    }
}

//===========================================================================================

void Play::Deffence_Geometry_making()
{

    double Deffence_Rad=1100;
    Vector2D B2GC=(Field::ourGoalCenter-wm->ball.pos.loc);
    double Dist_Ball_2_Goal=B2GC.length();//wm->ball.pos.loc-Field::ourGoalCenter).length();
    //    qDebug() << "Dis Ball2Goal" << Dist_Ball_2_Goal<<" ,  Deffence_Rad" << Deffence_Rad;

    if(Dist_Ball_2_Goal>Deffence_Rad) Dist_2_Deffence=Dist_Ball_2_Goal-Deffence_Rad;
    else Dist_2_Deffence=-100;



    Vector2D B2LG=(Field::ourGoalPost_L - wm->ball.pos.loc);
    Vector2D B2RG=(Field::ourGoalPost_R - wm->ball.pos.loc);
    double ang = (B2RG.dir().radian()-B2LG.dir().radian());

    //=========== 1st ====================================================
    //        double L_ang = B2LG.dir().radian()+0.15*ang;
    //        double R_ang = B2RG.dir().radian()-0.15*ang;
    //        //        qDebug() << "L_ang" << L_ang << " , R_ang" << R_ang;
    //        Vector2D B2LD,B2RD; // Ball to Left/Right Deffence
    //        B2LD.setPolar(Dist_2_Deffence,AngleDeg::rad2deg(L_ang));
    //        B2RD.setPolar(Dist_2_Deffence,AngleDeg::rad2deg(R_ang));
    //        Right_loc=wm->ball.pos.loc-B2RD;
    //        Left_loc=wm->ball.pos.loc-B2LD;
    //======================End 1st Mode=================================

    //=========================2nd=======================================
    Vector2D B2DC=B2GC; // Defining Ball 2 Center Of Deffence
    B2DC.setLength(Dist_2_Deffence);
    Deffence_center=wm->ball.pos.loc+B2DC;
    Wall_length=2*Dist_2_Deffence*tan(ang/2); // length of Deffence Wall which fully protected goal
    //        if(Dist_2_Deffence<700 && Dist_2_Deffence > 0) Wall_length = 300 ;
    Wall=B2GC;
    Wall.setLength(Wall_length); Wall.rotate(90);


    //======================End 2nd Mode=================================






    //    qDebug() << "Dist Deff" << Dist_2_Deffence;
    //    qDebug() << "Deff_Length" << Deffence_Length << "Tan " << tan(ang/2) << "Ang" << ang*180/3.14;


}

//===========================================================================================

Position Play::Find_OppRobot_BallOwner()
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
    if(ans!=-1 && num<2 && mindist < 400)
    {
        BallOwner_Finded=true;
        qDebug() << " Opponent Robot Number Has Owned The Ball: " << ans ;
        return wm->oppRobot[ans].pos;
    }

    else
    {
        Position Nosolution;
        Nosolution.loc=Vector2D(-1,-1);
        Nosolution.dir=-1;
        BallOwner_Finded=false;
        return Nosolution;
    }

}
