#include "skill.h"

Skill::Skill(WorldModel *wm, QObject *parent) :
    QObject(parent)
{
    this->wm = wm;
}

void Skill::setIndex(int id)
{
    this->index = id;
}
