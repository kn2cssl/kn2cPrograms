#ifndef FREEKICK3_H
#define FREEKICK3_H

#include "freekick_base.h"

class freeKick3 : public freeKick_base
{
    Q_OBJECT
public:
    explicit freeKick3(WorldModel *wm ,QObject *parent = 0);
    virtual int enterCondition();
    virtual void execute();

private:
    void setPositions(QList<int> our);
    int state;
};

#endif // FREEKICK3_H
