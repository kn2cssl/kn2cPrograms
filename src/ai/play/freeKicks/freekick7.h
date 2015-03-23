#ifndef freeKick7_H
#define freeKick7_H

#include "freekick_base.h"

class freeKick7 : public freeKick_base
{
    Q_OBJECT
public:
    explicit freeKick7(WorldModel *wm ,QObject *parent = 0);
    virtual int enterCondition(Level level);
    virtual void execute();
    virtual void resetValues();

private:
    void setPositions(QList<int> our);
    bool zeroCheckAttackersDistance();
    bool firstCheckDistance();
    void initRolesB(int AttackerLeft,int DefenderLeft);

    int state;
    int AttackerLeft;
    int DefenderLeft;
};

#endif // freeKick7_H
