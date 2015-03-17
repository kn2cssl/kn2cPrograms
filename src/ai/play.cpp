#include "play.h"

Play::Play(QString name, WorldModel *worldmodel, QObject *parent) :
    QObject(parent),
    name(name),alaki1(0,0),alaki2(100,0),
    Ball_2_Left_Goal(alaki1,alaki2),Ball_2_Right_Goal(alaki1,alaki2)
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

void Play::zonePositions(int leftID, int RightID, Position &goalie, Position &left, Position &right)
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
        Player1 = Find_OppRobot_BallOwner();
        Deffence_Geometry_making();

        if(!BallOwner_Finded)// NIST dar ekhtiare kesi  >> Ref2b(ball)
        {
            Ref_2Deff_Ball();
        }

        else if(BallOwner_Finded)
        {
            Ref_2Deff_Player(Player1);
        }


        left.loc = Left_loc;
        right.loc = Right_loc;
        left.dir =(wm->ourRobot[leftID].pos.loc - Field::ourGoalPost_L).dir().radian();
        right.dir=(wm->ourRobot[RightID].pos.loc - Field::ourGoalPost_R).dir().radian();
        //        UseNav = false ;
        //        qDebug() <<"Left Deffence " << left.loc.x << "," << left.loc.y ;
        //        qDebug() <<"Right Deffence " << right.loc.x << "," << right.loc.y ;

        //---------------------------------------------------------------------------------------


        // -----------------------------------------------------------------------
    }
}


//===========================================================================================

void Play::Ref_2Deff_Player(Position p)
{
    Segment2D LG2RG(Field::ourGoalPost_L,Field::ourGoalPost_R); // Left Goal to Right Goal
    Line2D L2R(Vector2D(Field::ourGoalCenter.x,FIELD_MAX_Y),Vector2D(Field::ourGoalCenter.x,-FIELD_MAX_Y));
    Line2D B2OT(wm->ball.pos.loc,AngleDeg::rad2deg(p.dir)); //Ball to Opponent Target
    Vector2D intersect_Point = L2R.intersection(B2OT);
    qDebug() << intersect_Point.x << " , " << intersect_Point.y;
    qDebug() << Field::ourGoalPost_R.y << " , " << Field::ourGoalPost_L.y ;
    if((intersect_Point.y > Field::ourGoalPost_R.y-100) && (intersect_Point.y < Field::ourGoalPost_L.y+100))
    {
        Vector2D B2DC = Deffence_center - wm->ball.pos.loc;
        double Rot_ang = (Player1.dir - B2DC.dir().radian());
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
