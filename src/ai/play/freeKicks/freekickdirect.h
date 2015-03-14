#ifndef FREEKICKDIRECT_H
#define FREEKICKDIRECT_H

#include "freekick_base.h"
#include "positioning.h"

class freeKickDirect : public freeKick_base
{
    Q_OBJECT
public:
    explicit freeKickDirect(WorldModel *wm ,QObject *parent = 0);
    virtual int enterCondition(Level level);
    virtual void execute();

private:
    void setPositions();
    int state;
    Vector2D target;
};

#endif // FREEKICKDIRECT_H

