#ifndef SKILLONETOUCH_H
#define SKILLONETOUCH_H

#include <QObject>
#include "skill.h"

class SkillOneTouch : public Skill
{
    Q_OBJECT
public:
    explicit SkillOneTouch(WorldModel* wm, QObject *parent = 0);
    bool execute(RobotCommand& rc);
    void setTarget(const Vector2D& Target);

private:
    Vector2D _Target;
    Line2D *Ball2C;
    Vector2D ballvel;
    Vector2D last_ballvel;
    Circle2D CR;//the circle that is painted around the receiver
    Vector2D currentposition;
    bool firstTime;
};

#endif // SKILLONETOUCH_H
