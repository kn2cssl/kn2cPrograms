#ifndef SKILLTEST_H
#define SKILLTEST_H

#include <QObject>
#include "skill.h"


class SkillTest : public Skill
{
    Q_OBJECT
public:
    explicit SkillTest(WorldModel* wm, QObject *parent = 0);
    bool execute(RobotCommand& rc , int index);
    void setTarget(const Vector2D& Target);




private:
    Vector2D _Target;
    Line2D *Ball2C;
    Vector2D ballvel={500,500};
    Vector2D last_ballvel={-500,500};
    Circle2D C;

};

#endif // SKILLTEST_H
