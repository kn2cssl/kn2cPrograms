#ifndef SKILLKICK_H
#define SKILLKICK_H

#include <QObject>
#include "skill.h"

#define lossFactor 1


class SkillKick : public Skill
{
    Q_OBJECT
public:
    explicit SkillKick(WorldModel* wm, QObject *parent = 0);
    bool execute(RobotCommand& rc);
    void setTarget(const Vector2D& Target);

private:
    Vector2D _Target;
    bool passFlag;
};

#endif // SKILLKICK_H
