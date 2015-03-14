#ifndef PLAYFREEKICKOUR_H
#define PLAYFREEKICKOUR_H

#include "play.h"
#include "freeKicks/freeKicks.h"

class PlayFreeKickOur : public Play
{
    Q_OBJECT
public:
    explicit PlayFreeKickOur(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    virtual int enterCondition();
private:
    virtual void initRole();
    QList<freeKick_base*> fk;
    freeKick_base *freeKick;
    bool freeKickSelected;

};

#endif // PLAYFREEKICKOUR_H
