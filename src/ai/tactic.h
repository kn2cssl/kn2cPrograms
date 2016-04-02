#ifndef TACTIC_H
#define TACTIC_H

#include <QObject>
#include "robotcommand.h"
#include "worldmodel.h"
#include "Skills.h"

class Tactic : public QObject
{
    Q_OBJECT
public:
    explicit Tactic(QString name, WorldModel *worldmodel, QObject *parent = 0);
    QString getName();
    virtual RobotCommand getCommand() = 0;
    void setID(int id);
    int getID();
    tANDp findTarget();
    void setPlayerToKeep(int index);
    float detectChipSpeed(bool shoot_sensor);

protected:
    Vector2D last_ball_vell;
    QTime f10s;//reset:check
    bool kickPermission;//reset:check
    int sensorFault = 0;//reset:check
    Vector2D ballDisplacement={0,0};//reset:check
    int startProbability=0;//reset:check
    bool timer_reset=false;

protected:
    WorldModel *wm;
    QString param;
    int playerToKeep;
    int id;

private:
    QString name;

};

#endif // TACTIC_H
