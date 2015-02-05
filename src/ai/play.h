#ifndef PLAY_H
#define PLAY_H

#include <QObject>
#include "worldmodel.h"
#include "tactics.h"

class Play : public QObject
{
    Q_OBJECT
public:
    explicit Play(QString name, WorldModel *worldmodel, QObject *parent = 0);
    QString getName();
    virtual void execute() = 0;
    virtual Tactic* getTactic(int id);
    virtual int enterCondition() = 0;
    bool conditionChanged();


protected:
    WorldModel *wm;
    QString param;
    Tactic *tactics[PLAYERS_MAX_NUM];
    virtual void initRole() = 0;

    int numberOfDef;
    int numberOfPlayers;
    bool rolesIsInit;

private:
    QString name;

};

#endif // PLAY_H
