#ifndef KICK_LEARNING_H
#define KICK_LEARNING_H

#define TOTAL_SAMPLE_TIME 3000

#include <QObject>
#include "learning/hillclimbing.h"
#include "worldmodel.h"

class Kick_Learning : public HillClimbing
{
    Q_OBJECT
public:
    explicit Kick_Learning(QObject *parent = 0);
    void set_kickTarget(Vector2D target);
    virtual void reward();
    bool end_of_sampling();
    void set_worldModel(WorldModel *wm);
    virtual void evaluate();

signals:

public slots:

private:
    WorldModel *wm;
    int numberOfSamples;
    int totalSamples;
    Vector2D kickTarget;
    double templateScore;

};

#endif // KICK_LEARNING_H
