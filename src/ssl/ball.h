#ifndef BALL_H
#define BALL_H

#include "mobileobject.h"
#include <QList>

class Ball : public MobileObject
{
    Q_OBJECT

public:
    explicit Ball();
    QList<Vector2D> *debugs;
    virtual void seenAt(vector<PositionTimeCamera> p);
};

#endif // BALL_H
