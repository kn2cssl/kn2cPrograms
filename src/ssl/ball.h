#ifndef BALL_H
#define BALL_H

#include "mobileobject.h"

class Ball : public MobileObject
{
    Q_OBJECT

public:
    explicit Ball();
    virtual void seenAt(vector<Position> p, double t, int c);


};

#endif // BALL_H
