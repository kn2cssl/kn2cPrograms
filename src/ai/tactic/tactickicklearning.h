#ifndef TACTICKICKLEARNING_H
#define TACTICKICKLEARNING_H

#include "tactic.h"
#include "learning/kick_learning.h"


/*  We use parameter[0] for DistErr
 *  and
 *  parameter[1] for DirErr  */

class TacticKickLearning : public Tactic
{
    Q_OBJECT
public:
    explicit TacticKickLearning(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();

    OperatingPosition kickForLearn(Vector2D Target , int Prob ,  int ID , double maxSpeed, Policy* policy, int Task=0);

    Position queuePos;
    bool kickIt;
    Vector2D kickTarget;
    Kick_Learning* hillClimber;
    Policy* current_policy;
};

#endif // TACTICKICKLEARNING_H
