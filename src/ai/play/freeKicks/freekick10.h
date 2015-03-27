#ifndef FREEKICK10_H
#define FREEKICK10_H

#include "freekick_base.h"

/*
 * freeKIck naghesss
 * */
class freeKick10 : public freeKick_base
{
    Q_OBJECT
public:
    explicit freeKick10(WorldModel *wm ,QObject *parent = 0);
    virtual int enterCondition(Level level);
    virtual void execute();
    virtual void resetValues();

private:
    void setPositions(QList<int> our);
    int state;
    int counter;
};

#endif // FREEKICK10_H
