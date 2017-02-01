#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include "soccer.h"
#include "fpscounter.h"

#define Pi 3.141592653589793238

#define WORLD_SCALE 10
#define DOUBLE_CENTER_X 476
#define DOUBLE_CENTER_Y 319
#define SINGLE_CENTER_X 370
#define SINGLE_CENTER_Y 270

#define ROBOT_R 9
#define ROBOT_D 18

#define BALL_R 4
#define NODE 4

#define ANGLE_TO_CHORD(a) 16*((a)*180/Pi+40), 16*280

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(Soccer *sc);
private:
    Soccer* _sc;
    QBrush *brush_field ,*brush_goals, *brush_ball, *brush_yrobot,*brush_brobot,*brush_test,
    *brush_astarNode, *brush_astarResult ,*brush_marking ,*brush_debug , *brush_pass;
    QTimer _timer;
    FPSCounter _fps;
    int CENTER_X,CENTER_Y;

signals:

public slots:
    void refresh();
    void paintEvent(QPaintEvent *);

};

#endif // RENDERAREA_H
