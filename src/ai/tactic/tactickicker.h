#ifndef TACTICKICKER_H
#define TACTICKICKER_H

#include "tactic.h"

class TacticKicker : public Tactic
{
    Q_OBJECT
public:
    explicit TacticKicker(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();

    RobotCommand goBehindBall();
    int findBestPlayerForPass();
    void setKickerID(int index);

    bool kicked;

private:
    bool canKick;
    bool firstKick;
    QTimer *timer;
    bool isFree(int index);
private slots:
    void timerEvent();

};

#endif // TACTICKICKER_H
