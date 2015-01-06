#ifndef KNOWLEDGE_H
#define KNOWLEDGE_H

#include <QtCore>
#include "geom.h"
#include "position.h"

class WorldModel;

class Knowledge : public QObject
{
    Q_OBJECT
public:
    explicit Knowledge(WorldModel* wm, QObject *parent = 0);
    int CountActiveAgents();
    QList<int> ActiveAgents();
    QList<int> ActiveOppAgents();
    QList<int> findNearestTo(Vector2D loc);
    QList<int> findNearestOppositeTo(Vector2D loc);
    int findOppAttacker();

    void ClampToRect(Vector2D *pos, Vector2D topLeft, Vector2D bottomRight);
    bool IsInsideRect(Vector2D pos, Vector2D topLeft, Vector2D bottomRight);
    bool IsInsideCircle(Vector2D pos,Vector2D center,double radios);
    bool IsInsideField(Vector2D pos);
    bool IsInsideOurField(Vector2D pos);

    bool IsInsideGoalShape(Vector2D pos, double goalLeftX, double goalRadius, double goalCcOffset);
    bool IsInsideGolieArea(Vector2D pos);
    bool IsInsideSecureArea(Vector2D pos,Vector2D ball);

    bool CanKick(Position robotPos, Vector2D ballPos);
    bool IsReadyForKick(Position current, Position desired, Vector2D ballPos);
    Position AdjustKickPoint(Vector2D ballPos, Vector2D target, int kickSpeed = 5);
    Position AdjustKickPoint2(Vector2D ballPos, Vector2D target, Vector2D robotloc);

    Vector2D PredictDestination(Vector2D sourcePos, Vector2D targetPos, double sourceSpeed, Vector2D targetSpeed);
    bool ReachedToPos(Position current, Position desired, double distThreshold, double degThreshold);
    bool ReachedToPos(Vector2D current, Vector2D desired, double distThreshold);

    bool agentIsFree(int index);
    bool isOccupied(Vector2D input);

private:
    WorldModel* _wm;

signals:

public slots:

};

#endif // KNOWLEDGE_H
