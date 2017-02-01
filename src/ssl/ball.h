#ifndef BALL_H
#define BALL_H

#include "mobileobject.h"

class Ball : public MobileObject
{
    Q_OBJECT

public:
    explicit Ball();
    virtual void seenAt(vector<PositionTimeCamera> p);
};

#endif // BALL_H
