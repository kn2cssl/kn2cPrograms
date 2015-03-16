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
        Deffence_Geometry_making();

        left.loc=Left_loc;
        right.loc=Right_loc;
        left.dir=(wm->ball.pos.loc-wm->ourRobot[leftID].pos.loc).dir().radian();
        right.dir=(wm->ball.pos.loc-wm->ourRobot[RightID].pos.loc).dir().radian();
        //        qDebug() <<"Left Deffence " << left.loc.x << "," << left.loc.y ;
        //        qDebug() <<"Right Deffence " << right.loc.x << "," << right.loc.y ;

        //---------------------------------------------------------------------------------------


        // -----------------------------------------------------------------------
    }
}

Position Play::Ref_1Deff_Player(Position)
{

}

void Play::Deffence_Geometry_making()
{
    Find_OppRobot_BallOwner();


    Ball_2_Left_Goal.assign(wm->ball.pos.loc,Field::ourGoalPost_L);
    Ball_2_Right_Goal.assign(wm->ball.pos.loc,Field::ourGoalPost_R);
    double Deffence_Rad=1000;
    double Dist_Ball_2_Goal=(wm->ball.pos.loc-Field::ourGoalCenter).length();
    //    qDebug() << "Dis Ball2Goal" << Dist_Ball_2_Goal<<" ,  Deffence_Rad" << Deffence_Rad;

    double Dist_2_Deffence;
    if(Dist_Ball_2_Goal>Deffence_Rad) Dist_2_Deffence=Dist_Ball_2_Goal-Deffence_Rad;
    else Dist_2_Deffence=-200;

    //=========== 1st ====================================================
    Vector2D B2LG=(Ball_2_Left_Goal.origin()-Ball_2_Left_Goal.terminal());
    Vector2D B2RG=(Ball_2_Right_Goal.origin()-Ball_2_Right_Goal.terminal());
    double ang = (B2RG.dir().radian()-B2LG.dir().radian());
    if(!BallOwner_Finded)// NIST dar ekhtiare kesi  >> Ref2b(ball)
    {
        double L_ang = B2LG.dir().radian()+0.15*ang;
        double R_ang = B2RG.dir().radian()-0.15*ang;
        //        qDebug() << "L_ang" << L_ang << " , R_ang" << R_ang;
        Vector2D B2LD,B2RD; // Ball to Left/Right Deffence
        B2LD.setPolar(Dist_2_Deffence,AngleDeg::rad2deg(L_ang));
        B2RD.setPolar(Dist_2_Deffence,AngleDeg::rad2deg(R_ang));
        Right_loc=wm->ball.pos.loc-B2RD;
        Left_loc=wm->ball.pos.loc-B2LD;
    }
    //======================End 1st Mode=================================
    //=========================2nd=======================================
    //    Vector2D B2GC=(wm->ball.pos.loc,)
    //======================End 2nd Mode=================================
    else if(BallOwner_Finded)
    {
        qDebug() << " FIIIIIIIIIIIIIIIIIIIIIIIIInded !!! " ;
    }



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
            qDebug() << " Min Dist " << mindist;
            ans=jj;
        }
    }
    if(ans!=-1 && num<2)
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
