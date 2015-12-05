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
    virtual bool execute(RobotCommand& rc, int id = 0) = 0;

protected:
    WorldModel *wm;

};

#endif // SKILL_H
