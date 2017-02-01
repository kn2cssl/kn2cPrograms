#ifndef MOBILEOBJECT_H
#define MOBILEOBJECT_H

#include <QDebug>
#include <QTimer>
#include <vector>
using namespace std;

#include "geom.h"
#include "position.h"

#define LAST_COUNT 4

struct PositionTimeCamera
{
    Position pos;

    double time;
    int camera;
    double confidence;
    PositionTimeCamera()
    {
        time = 0;
        camera = 0;
    }
};

class MobileObject : public QObject
{
    Q_OBJECT

public:
    explicit MobileObject();
    virtual void seenAt(vector<PositionTimeCamera>) = 0;

    bool isValid;

    Position pos;
    Position pos_predicted;
    double time;
    int camera,camera_mem;

    int camera_timeout;

    Position vel;

protected:
    PositionTimeCamera last_postc[LAST_COUNT];
    PositionTimeCamera vel_postc;
    void appendPostc(PositionTimeCamera &postc);

//private:
    QTimer timer_seen;
    int    timer_seen_interval;
    QTimer timer_vel;
    int    timer_vel_interval;
    void   vel_calc();

private slots:
    void timer_seen_timeout();
    void timer_vel_timeout();

};

#endif // MOBILEOBJECT_H
