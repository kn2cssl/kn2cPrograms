#ifndef FREEKICK1_H
#define FREEKICK1_H

#include "freekick_base.h"

class freeKick1 : public freeKick_base
{
public:
    explicit freeKick1(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    virtual int enterCondition(Level level);

private:
    void setPositions();
    bool firstTimeInitial;
};

#endif // FREEKICK1_H
