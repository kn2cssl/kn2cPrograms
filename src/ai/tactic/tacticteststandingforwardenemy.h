#ifndef TACTICTESTSTANDINGFORWARDENEMY_H
#define TACTICTESTSTANDINGFORWARDENEMY_H
#include "tactic.h"
#define DangerDist 300
#include "geom.h"
#include "constants.h"

class TacticTestStandingForwardEnemy : public Tactic
{
private:
    //distanse between enemy and ally robot
    int distance;
    int OppRobotIndex;
    Q_OBJECT
public:
    TacticTestStandingForwardEnemy();
    explicit TacticTestStandingForwardEnemy(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
    int getDistance() const;
    void setDistance(int value);
    int getOppRobotIndex() const;
    void setOppRobotIndex(int value);
};

#endif // TACTICTESTSTANDINGFORWARDENEMY_H
