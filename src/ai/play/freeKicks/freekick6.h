#ifndef freeKick6_H
#define freeKick6_H

#include "freekick_base.h"
#include "positioning.h"

class freeKick6 : public freeKick_base
{
    Q_OBJECT
public:
    explicit freeKick6(WorldModel *wm ,QObject *parent = 0);
    virtual int enterCondition();
    virtual void execute();

private:
    void setPositions();
    bool checkAttackersDistance();
    int state;
    Vector2D target;
};

#endif // freeKick6_H
