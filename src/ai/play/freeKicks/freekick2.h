#ifndef FREEKICK2_H
#define FREEKICK2_H

#include <QObject>
#include "freekick_base.h"

class freeKick2 : public freeKick_base
{
    Q_OBJECT
public:
    explicit freeKick2(WorldModel *wm,QObject *parent = 0);
    virtual int enterCondition(Level level);
    virtual void execute();

private:
    void setPositions(int index);

};

#endif // FREEKICK2_H
