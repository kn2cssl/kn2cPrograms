#ifndef FREEKICK9_H
#define FREEKICK9_H

#include "freekick_base.h"
#include "positioning.h"

class freeKick9 : public freeKick_base
{
    Q_OBJECT
public:
    explicit freeKick9(WorldModel *wm ,QObject *parent = 0);
    virtual int enterCondition(Level level);
    virtual void execute();
    virtual void resetValues();

private:
    void setPositions(QList<int> our);
    int state;
    Vector2D defaultPos;
};

#endif // FREEKICK9_H
