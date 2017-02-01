#include "worldmodel.h"

double WorldModel::var[10];

WorldModel::WorldModel(OutputBuffer *outputBuffer)
{
    time = 0;
    ref_goalie_our = 0;
    ref_goalie_opp = 0;
    gs = STATE_Null;
    gs_last = STATE_Null;
    isSim = false;
    kn = new Knowledge(this);

    for(int i=0; i<PLAYERS_MAX_NUM; i++)
    {
        ourRobot[i].setID(i);
        ourRobot[i].setOutputBuffer(outputBuffer);
        ourRobot[i].setWorldModel(this);
    }

    for(int i=0; i<10; i++)
        var[i] = 0;

    for(int i=0; i<6; i++)
        pos_coef[i] = 0;

    for(int i=0; i<6; i++)
        mark_coef[i] = 0;

    oppLevel_fk = Level::Beginner;

    for(int i=0;i<NUMBEROFFREEKICKS;i++)
        select_fk[i] = false;

    useShootSensor = true;

    defenceMode = false;

    useVoronoi = false;

    use4Player4Marking = false;

    climbing_status = "stopped";
    policy_index = 0;
    iteration_index = 0;
    climbing_start = false;
    save_policies = false;
    load_policies = false;
}
