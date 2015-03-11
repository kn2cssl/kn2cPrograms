#ifndef TACTICCONTROL_H
#define TACTICCONTROL_H
#include "tactic.h"
#define DangerDist 300
class tacticControl : public Tactic
{
    Q_OBJECT
public:
    explicit tacticControl(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
    RobotCommand goBehindBall();
    int findBestPlayerForPass();
    void setKickerID(int index);
    bool kicked;
private:
    bool canKick;
    bool firstKick;
    double alfa;
    int state;
    QTimer *timer;
    bool isFree(int index);
private slots:
    void timerEvent();
};
#endif // tacticControl_H
