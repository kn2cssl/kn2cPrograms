#ifndef TACTIC_H
#define TACTIC_H

#include <QObject>
#include "robotcommand.h"
#include "worldmodel.h"

class Tactic : public QObject
{
    Q_OBJECT
public:
    explicit Tactic(QString name, WorldModel *worldmodel, QObject *parent = 0);
    QString getName();
    virtual RobotCommand getCommand() = 0;
    void setID(int id);
    int getID();
    Vector2D findTarget();
    void setPlayerToKeep(int index);
    float detectKickSpeed(Vector2D dest = Vector2D(0,0) );

protected:
    WorldModel *wm;
    QString param;
    int playerToKeep;
    int id;

private:
    QString name;

};

#endif // TACTIC_H
