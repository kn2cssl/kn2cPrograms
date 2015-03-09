#include "playfreekickour.h"
PlayFreeKickOur::PlayFreeKickOur(WorldModel *worldmodel, QObject *parent) :
    Play("PlayFreeKickOur", worldmodel, parent)
{
    fk.append(new freeKick1(wm));
    fk.append(new freeKick2(wm));
    fk.append(new freeKick3(wm));
    fk.append(new freeKick4(wm));
}
int PlayFreeKickOur::enterCondition()
{
    if(wm->cmgs.ourFreeKick() || wm->cmgs.ourIndirectKick())
    {
        if(wm->gs_last != wm->gs)
        {
            rolesIsInit = false;
        }
        else
        {
            rolesIsInit = conditionChanged();
        }
        return 100;
    }
    else
        return 0;
    return 0;
    // return 2000000;
}

void PlayFreeKickOur::initRole()
{

}

void PlayFreeKickOur::execute()
{
    int max_i = 0;
    int max_p = 0;
    for(int i=0; i<fk.size(); i++)
    {
        int p = fk[i]->enterCondition();
        if(p > max_p)
        {
            max_i = i;
            max_p = p;
        }
    }

    freeKick_base *freeKick = fk[max_i];
    freeKick->execute();

    for(int i=0; i<PLAYERS_MAX_NUM; i++)
    {
        Tactic *tactic = freeKick->getTactic(i);
        if(tactic == NULL) continue;
        tactics[i] = tactic;
    }
}
