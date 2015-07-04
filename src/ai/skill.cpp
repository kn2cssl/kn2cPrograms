#include "skill.h"

Skill::Skill(WorldModel *wm, QObject *parent) :
    QObject(parent)
{
    this->wm = wm;
}
