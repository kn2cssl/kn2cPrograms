#ifndef SKILLONETOUCH_H
#define SKILLONETOUCH_H

//#define lowPassFilterFactor 0.2

#include <QObject>
#include "skill.h"

class SkillOneTouch : public Skill
{
    Q_OBJECT
public:
    explicit SkillOneTouch(WorldModel* wm, QObject *parent = 0);
    bool execute(RobotCommand& rc);
    void setTarget(const Vector2D target);
    void setPosition(const Vector2D position);

private:
    Vector2D position;
    Vector2D target;
    Vector2D currentposition;
    bool firstTime;


    //////////////////////////////////////////////////version 1.0
    bool movementFlag=true;
    Vector2D goal;
    Line2D *robotLine;
    double ballVelAngel;
    Circle2D robotCircle;
    //////////////////////////////////////////////////

};

#endif // SKILLONETOUCH_H
