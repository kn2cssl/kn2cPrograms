#ifndef SKILLTEST_H
#define SKILLTEST_H

#include <QObject>
#include "skill.h"

class SkillTest : public Skill
{
    Q_OBJECT
public:
    explicit SkillTest(WorldModel* wm, QObject *parent = 0);
    bool execute(RobotCommand& rc);

};

#endif // SKILLTEST_H
