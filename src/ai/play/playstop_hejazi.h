#ifndef PLAYSTOP_HEJAZI_H
#define PLAYSTOP_HEJAZI_H
#include "play.h"
#include <QObject>

class PlayStop_Hejazi : public Play
{
public:
    explicit PlayStop_Hejazi(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    virtual void initRole();
    PlayStop_Hejazi();
};

#endif // PLAYSTOP_HEJAZI_H
