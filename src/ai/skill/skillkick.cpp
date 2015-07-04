#include "skillkick.h"

SkillKick::SkillKick(WorldModel* wm, QObject *parent) :
    Skill(wm, parent)
{
}

bool SkillKick::execute(RobotCommand &rc)
{

}

void SkillKick::setTarget(const Vector2D &Target)
{
    _Target=Target;
}
