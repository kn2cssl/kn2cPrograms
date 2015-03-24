#include "playfreekickour.h"
PlayFreeKickOur::PlayFreeKickOur(WorldModel *worldmodel, QObject *parent) :
    Play("PlayFreeKickOur", worldmodel, parent)
{
    freeKickSelected = false;

    fk.append(new freeKick1(wm));
    fk.append(new freeKick2(wm));
    fk.append(new freeKick3(wm));
    fk.append(new freeKick4(wm));
    fk.append(new freeKick5(wm));
    fk.append(new freeKick6(wm));
    fk.append(new freeKick7(wm));
    fk.append(new freeKick8(wm));
    fk.append(new freeKick9(wm));
    fk.append(new freeKick10(wm));
    fk.append(new freeKick11(wm));
    fk.append(new freeKick47(wm));
    fk.append(new freeKickDirect(wm));
}
int PlayFreeKickOur::enterCondition()
{
    if(wm->cmgs.ourFreeKick() || wm->cmgs.ourIndirectKick())
    {
        if(wm->gs_last != wm->gs)
        {
            rolesIsInit = false;
            freeKickSelected = false;
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
}

void PlayFreeKickOur::initRole()
{

}

void PlayFreeKickOur::execute()
{
    if( !freeKickSelected )
    {
        for(int i=0;i<fk.size();i++)
        {
            freeKick_base* tmp = fk.at(i);
            tmp->resetValues();
        }
        QList<freeKick_base*> candidates;

        int max_i = 0;
        int max_p = 0;

        for(int i=0; i<fk.size(); i++)
        {
            int p = fk[i]->enterCondition(wm->oppLevel_fk);
            if(p > max_p)
            {
                max_i = i;
                max_p = p;
                candidates.clear();
                candidates.append(fk[i]);
            }
            else if ( p == max_p )
            {
                candidates.append(fk[i]);
            }
        }

        srand(time(NULL));
        int finalNum = rand()%(candidates.size());

        freeKick = candidates.at(finalNum);
        freeKickSelected = true;
    }

    freeKick->execute();

    for(int i=0; i<PLAYERS_MAX_NUM; i++)
    {
        Tactic *tactic = freeKick->getTactic(i);
        if(tactic == NULL) continue;
        tactics[i] = tactic;
    }
}
