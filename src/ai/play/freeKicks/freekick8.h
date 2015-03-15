#ifndef freeKick8_H
#define freeKick8_H

#include "freekick_base.h"
#include "positioning.h"

class freeKick8 : public freeKick_base
{
    Q_OBJECT
public:
    explicit freeKick8(WorldModel *wm ,QObject *parent = 0);
    virtual int enterCondition(Level level);
    virtual void execute();

private:
    void setPositions();
    int state;
    Vector2D target;
};

#endif // freeKick8_H
