#include "playfreekickour.h"
PlayFreeKickOur::PlayFreeKickOur(WorldModel *worldmodel, QObject *parent) :
    Play("PlayFreeKickOur", worldmodel, parent)
{
    freeKickSelected = false;
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

        fk.clear();

        if( wm->select_fk[0] )
            fk.append(new freeKickDirect(wm));

        if( wm->select_fk[1] )
            fk.append(new freeKick1(wm));

        if( wm->select_fk[2] )
            fk.append(new freeKick2(wm));

        if( wm->select_fk[3] )
            fk.append(new freeKick3(wm));

        if( wm->select_fk[4] )
            fk.append(new freeKick4(wm));

        if( wm->select_fk[5] )
            fk.append(new freeKick5(wm));

        if( wm->select_fk[6] )
            fk.append(new freeKick6(wm));

        if( wm->select_fk[7] )
            fk.append(new freeKick7(wm));

        if( wm->select_fk[8] )
            fk.append(new freeKick8(wm));

        if( wm->select_fk[9] )
            fk.append(new freeKick9(wm));

        if( wm->select_fk[10] )
            fk.append(new freeKick10(wm));

        if( wm->select_fk[11] )
            fk.append(new freeKick11(wm));

<<<<<<< HEAD
        if(wm->select_fk[12])
            fk.append(new freeKickTest2(wm));
=======
        wm->select_fk[12]=true;
        if( wm->select_fk[12] )
            fk.append(new freekicktest1(wm));
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28

        if( wm->select_fk[NUMBEROFFREEKICKS-1] )
            fk.append(new freeKick47(wm));

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
