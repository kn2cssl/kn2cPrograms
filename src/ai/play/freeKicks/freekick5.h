#ifndef freeKick5_H
#define freeKick5_H

#include "freekick_base.h"
#include "positioning.h"

class freeKick5 : public freeKick_base
{
    Q_OBJECT
public:
    explicit freeKick5(WorldModel *wm ,QObject *parent = 0);
    virtual int enterCondition();
    virtual void execute();

private:
    void setPositions();
    bool checkAttackersDistance();
    int state;
    Vector2D target;
};

#endif // freeKick5_H
