#ifndef TACTICFORMATION_H
#define TACTICFORMATION_H

#include "tactic.h"

class TacticFormation : public Tactic
{
    Q_OBJECT
public:
    explicit TacticFormation(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
    void setLeaderID(int leaderID);
    void setInformations(int leaderID, int formationType);
    void setFixedPos(Vector2D vec);

private:
    int leaderID;
    int formationType;
    QList<Position> path;
    Vector2D fixedPos;

    int findPositionIndex(Position pos);
    int findPositionIndex(Position pos, double threshold);
};


#endif // TACTICFORMATION_H
