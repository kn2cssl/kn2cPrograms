#ifndef FREEKICK11_H
#define FREEKICK11_H

#include "freekick_base.h"

class freeKick11 : public freeKick_base
{
    Q_OBJECT
public:
    explicit freeKick11(WorldModel *wm ,QObject *parent = 0);
    virtual int enterCondition(Level level);
    virtual void execute();
    virtual void resetValues();

private:
    void setPositions(QList<int> our);
    int state;
};

#endif // FREEKICK11_H
