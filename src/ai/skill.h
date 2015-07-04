#ifndef SKILL_H
#define SKILL_H

#include <QObject>
#include "robotcommand.h"
#include "worldmodel.h"

class Skill : public QObject
{
    Q_OBJECT
public:
    explicit Skill(WorldModel *wm, QObject *parent = 0);
    virtual bool execute(RobotCommand& rc) = 0;

private:
    WorldModel *wm;

};

#endif // SKILL_H
