#ifndef SKILLKICK_H
#define SKILLKICK_H

#include <QObject>
#include "skill.h"


class SkillKick : public Skill
{
    Q_OBJECT
public:
    explicit SkillKick(WorldModel* wm, QObject *parent = 0);
    bool execute(RobotCommand& rc, int index);
    void setTarget(const Vector2D& Target);




private:
    Vector2D _Target;
    Line2D *Ball2C;
    Vector2D ballvel={500,500};
    Vector2D last_ballvel={-500,500};
    Circle2D C0,C1;

    bool kicker0=false;
    bool receiver0=false;

    bool kicker1=false;
    bool receiver1=false;

    bool kicker2=false;
    bool receiver2=false;

    bool decision=true;

    bool flag0=true;
    bool flag1=true;


};

#endif // SKILLKICK_H
