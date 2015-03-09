#ifndef freeKick4_H
#define freeKick4_H

#include "freekick_base.h"

class freeKick4 : public freeKick_base
{
    Q_OBJECT
public:
    explicit freeKick4(WorldModel *wm ,QObject *parent = 0);
    virtual int enterCondition();
    virtual void execute();

private:
    void setPositions(QList<int> our);
    int state;
};

#endif // freeKick4_H
