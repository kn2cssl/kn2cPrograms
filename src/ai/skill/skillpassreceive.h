#ifndef SKILLPASSRECEIVE_H
#define SKILLPASSRECEIVE_H

#include <QObject>
#include "skill.h"

class SkillPassReceive : public Skill
{
    Q_OBJECT
public:
    explicit SkillPassReceive(WorldModel* wm, QObject *parent = 0);
    bool execute(RobotCommand& rc);

private:
    Line2D *Ball2C;
    Vector2D ballvel;
    Vector2D last_ballvel;
    Circle2D CR;//the circle that is painted around the receiver

    Vector2D currentposition;
    bool firstTime;

};

#endif // SKILLPASSRECEIVE_H
