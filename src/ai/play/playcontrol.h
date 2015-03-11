#ifndef PLAYCONTROL_H
#define PLAYCONTROL_H
#include "play.h"

class playControl : public Play
{
    Q_OBJECT
public:
    explicit playControl(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    virtual void initRole();
    virtual int enterCondition();
    tacticControl* anghezy;
};
#endif // PLAYCONTROL_H
