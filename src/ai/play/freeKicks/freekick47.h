#ifndef FREEKICK47_H
#define FREEKICK47_H

#include "freekick_base.h"

class freeKick47 : public freeKick_base
{
    Q_OBJECT
public:
    explicit freeKick47(WorldModel *wm ,QObject *parent = 0);
    virtual int enterCondition(Level level);
    virtual void execute();
    virtual void resetValues();

private:
    void setPositions(QList<int> our);
    void initRolesB(int AttackerRight, int DefenderLeft);
    int state;
    int AttackerRight;
    int DefenderLeft;
};

#endif // FREEKICK47_H
