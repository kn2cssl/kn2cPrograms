#include "skilltest.h"


SkillTest::SkillTest(WorldModel *wm, QObject *parent) :
    Skill(wm, parent)
{
}

bool SkillTest::execute(RobotCommand &rc, int index)
{

        //RecievingPass....



        //locating

        rc.maxSpeed=3;
        rc.fin_pos.loc={0,0};


        Vector2D robot2ball=wm->ball.pos.loc-wm->ourRobot[index].pos.loc;
        rc.fin_pos.dir=robot2ball.dir().radian();

        //rc.fin_pos.loc={2470,0};


        if (wm->ball.vel.loc.length()>0.05)
        {
            Vector2D goal;
            Vector2D Ballpos=wm->ball.pos.loc;
            Ball2C = new Line2D(Ballpos , wm->ball.vel.loc.dir().degree());
            Vector2D A,B;

            ballvel.setDir(wm->ball.vel.loc.dir().degree());


            if(fabs(ballvel.dir().degree()-last_ballvel.dir().degree())>10)
            {

                C.assign(wm->ourRobot[index].pos.loc,ROBOT_RADIUS+500);

            }

            last_ballvel.setDir(ballvel.dir().degree());



            C.intersection(*Ball2C,&A,&B);

            if( C.HasIntersection(*Ball2C))
            {
                if((Ballpos-A).length2()>(Ballpos-B).length2())
                {
                    goal=B;
                }

                else
                {
                    goal=A;
                }

                rc.fin_pos.loc=goal;
                rc.fin_pos.dir=(wm->ball.vel.loc.dir().radian()+M_PI);//tttarget.dir().radian();//


            }



        }

//        Circle2D W(wm->ourRobot[index].pos.loc,150);
//        if(W.contains(wm->ball.pos.loc) && index==1)
//        {
//            flag=1;

//        }

//        if(W.contains(wm->ball.pos.loc) && index==0)
//        {
//            flag=0;
//        }


}
