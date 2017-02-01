#include "renderarea.h"

RenderArea::RenderArea(Soccer* sc) :
    QWidget()
{
    _sc = sc;
    QString pic_address;
    if( sc->field == "Double")
    {
        pic_address = ":/resources/images/Field2.jpg";
        this->CENTER_X = DOUBLE_CENTER_X;
        this->CENTER_Y = DOUBLE_CENTER_Y;
    }
    else
    {
        pic_address = ":/resources/images/Field.jpg";
        this->CENTER_X = SINGLE_CENTER_X;
        this->CENTER_Y = SINGLE_CENTER_Y;
    }

    brush_field = new QBrush(QPixmap(pic_address));
    brush_ball = new QBrush(QColor::fromRgb(255,200,0),Qt::SolidPattern);
    brush_yrobot = new QBrush(QColor::fromRgb(255,255,0),Qt::SolidPattern);
    brush_brobot = new QBrush(QColor::fromRgb(50,50,255),Qt::SolidPattern);
    brush_test = new QBrush(QColor::fromRgb(50,50,255),Qt::SolidPattern);
    brush_astarNode = new QBrush(QColor::fromRgb(50,50,255),Qt::SolidPattern);
    brush_astarResult = new QBrush(QColor::fromRgb(250,50,55),Qt::SolidPattern);
    brush_marking = new QBrush(QColor::fromRgb(0,0,0),Qt::SolidPattern);
    brush_goals = new QBrush(QColor::fromRgb(255,255,255),Qt::SolidPattern);
    brush_debug = new QBrush(QColor::fromRgb(255,0,0),Qt::SolidPattern);
    brush_pass = new QBrush(QColor::fromRgb(125,125,0),Qt::SolidPattern);
    _timer.start(40);
    connect(&_timer,SIGNAL(timeout()), this, SLOT(refresh()));
}

void RenderArea::refresh()
{
    update();
}

void RenderArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // Settings
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // Draw Field
    painter.setBrush(*brush_field);
    painter.drawRect(0,0,953,637);

    // FPS
    painter.drawText(15,15,QString::number(_fps.FPS()));

    painter.translate(CENTER_X,CENTER_Y);

    //Draw Our Goal
    QPoint our_left1(Field::ourGoalPost_L.x /WORLD_SCALE, -Field::ourGoalPost_L.y/WORLD_SCALE);
    QPoint our_left2( (Field::ourGoalPost_L.x - Field::GoalDeep) /WORLD_SCALE, -Field::ourGoalPost_L.y/WORLD_SCALE);
    QPoint our_right1(Field::ourGoalPost_R.x/WORLD_SCALE , -Field::ourGoalPost_R.y/WORLD_SCALE);
    QPoint our_right2( (Field::ourGoalPost_R.x - Field::GoalDeep) /WORLD_SCALE , -Field::ourGoalPost_R.y/WORLD_SCALE);
    painter.setBrush(*brush_goals);
    painter.setPen(QColor::fromRgb(255,255,255));
    painter.drawLine(our_left2,our_right2);
    painter.drawLine(our_left1,our_left2);
    painter.drawLine(our_right1,our_right2);

    //Draw Opp Goal
    QPoint opp_left1(Field::oppGoalPost_L.x /WORLD_SCALE, -Field::oppGoalPost_L.y/WORLD_SCALE);
    QPoint opp_left2( (Field::oppGoalPost_L.x + Field::GoalDeep) /WORLD_SCALE, -Field::oppGoalPost_L.y/WORLD_SCALE);
    QPoint opp_right1(Field::oppGoalPost_R.x/WORLD_SCALE , -Field::oppGoalPost_R.y/WORLD_SCALE);
    QPoint opp_right2( (Field::oppGoalPost_R.x + Field::GoalDeep) /WORLD_SCALE , -Field::oppGoalPost_R.y/WORLD_SCALE);
    painter.setBrush(*brush_goals);
    painter.setPen(QColor::fromRgb(255,255,255));
    painter.drawLine(opp_left2,opp_right2);
    painter.drawLine(opp_left1,opp_left2);
    painter.drawLine(opp_right1,opp_right2);

    // Draw Target lines !! MOHSEN
    if(_sc->wm->ball.isValid)
    {
        QPoint Pball;
        Pball.setX(_sc->wm->ball.pos.loc.x/WORLD_SCALE);
        Pball.setY(-_sc->wm->ball.pos.loc.y/WORLD_SCALE);

        if( _sc->wm->showDefenderDebug )
        {
            QPoint pnt;
            pnt.setX(Field::ourGoalPost_L.x/WORLD_SCALE); pnt.setY(-Field::ourGoalPost_L.y/WORLD_SCALE);
            painter.drawLine(pnt,Pball);

            pnt.setY(Field::ourGoalPost_L.y/WORLD_SCALE);
            painter.drawLine(pnt,Pball);

            pnt.setY(0);
            painter.drawLine(pnt,Pball);
        }
    }

    if( _sc->wm->showChances )
    {
        QPoint Pball;
        Pball.setX(_sc->wm->ball.pos.loc.x/WORLD_SCALE);
        Pball.setY(-_sc->wm->ball.pos.loc.y/WORLD_SCALE);

        //painter.setBrush(*brush_ball);
        if(_sc->wm->ball.isValid && _sc->wm->TANDPis.size() > 0 )
        {
            for(int i=0;i<_sc->wm->TANDPis.size();i++)
            {
                int tmp= 5.0*_sc->wm->TANDPis.at(i).prob;
                if(tmp>255) tmp=255;
                painter.setPen(QColor::fromRgb(0,tmp,tmp));
                QPoint pnt;
                pnt.setX(_sc->wm->TANDPis.at(i).pos.x/WORLD_SCALE); pnt.setY(-_sc->wm->TANDPis.at(i).pos.y/WORLD_SCALE);
                painter.drawLine(pnt,Pball);
            }

            int tmp= 2.5*_sc->wm->max_TANDPis.prob;
            painter.setPen(QColor::fromRgb(255,0,0));
            QPoint pnt;
            pnt.setX(_sc->wm->max_TANDPis.pos.x/WORLD_SCALE); pnt.setY(-_sc->wm->max_TANDPis.pos.y/WORLD_SCALE);
            painter.drawLine(pnt,Pball);

        }
    }

    // Draw Robots
    painter.setPen(QColor::fromRgb(0,0,0));

    if( _sc->wm->ourColor == TeamColorType::COLOR_BLUE )
    {
        painter.setBrush(*brush_yrobot);
        for(int i=0;i<12;i++)
            if(_sc->wm->oppRobot[i].isValid)
            {
                painter.drawChord(_sc->wm->oppRobot[i].pos.loc.x/WORLD_SCALE-ROBOT_R,-_sc->wm->oppRobot[i].pos.loc.y/WORLD_SCALE-ROBOT_R,ROBOT_D,ROBOT_D,ANGLE_TO_CHORD(_sc->wm->oppRobot[i].pos.dir));
                painter.drawText(_sc->wm->oppRobot[i].pos.loc.x/WORLD_SCALE-ROBOT_R,-_sc->wm->oppRobot[i].pos.loc.y/WORLD_SCALE-ROBOT_R,ROBOT_D,ROBOT_D,Qt::AlignCenter,QString::number(i));
            }

        painter.setBrush(*brush_brobot);
        for(int i=0;i<12;i++)
            if(_sc->wm->ourRobot[i].isValid)
            {
                painter.drawChord(_sc->wm->ourRobot[i].pos.loc.x/WORLD_SCALE-ROBOT_R,-_sc->wm->ourRobot[i].pos.loc.y/WORLD_SCALE-ROBOT_R,ROBOT_D,ROBOT_D,ANGLE_TO_CHORD(_sc->wm->ourRobot[i].pos.dir));
                painter.drawText(_sc->wm->ourRobot[i].pos.loc.x/WORLD_SCALE-ROBOT_R,-_sc->wm->ourRobot[i].pos.loc.y/WORLD_SCALE-ROBOT_R,ROBOT_D,ROBOT_D,Qt::AlignCenter,QString::number(i));
            }
    }
    else
    {
        painter.setBrush(*brush_yrobot);
        for(int i=0;i<12;i++)
            if(_sc->wm->ourRobot[i].isValid)
            {
                painter.drawChord(_sc->wm->ourRobot[i].pos.loc.x/WORLD_SCALE-ROBOT_R,-_sc->wm->ourRobot[i].pos.loc.y/WORLD_SCALE-ROBOT_R,ROBOT_D,ROBOT_D,ANGLE_TO_CHORD(_sc->wm->ourRobot[i].pos.dir));
                painter.drawText(_sc->wm->ourRobot[i].pos.loc.x/WORLD_SCALE-ROBOT_R,-_sc->wm->ourRobot[i].pos.loc.y/WORLD_SCALE-ROBOT_R,ROBOT_D,ROBOT_D,Qt::AlignCenter,QString::number(i));
            }

        painter.setBrush(*brush_brobot);
        for(int i=0;i<12;i++)
            if(_sc->wm->oppRobot[i].isValid)
            {
                painter.drawChord(_sc->wm->oppRobot[i].pos.loc.x/WORLD_SCALE-ROBOT_R,-_sc->wm->oppRobot[i].pos.loc.y/WORLD_SCALE-ROBOT_R,ROBOT_D,ROBOT_D,ANGLE_TO_CHORD(_sc->wm->oppRobot[i].pos.dir));
                painter.drawText(_sc->wm->oppRobot[i].pos.loc.x/WORLD_SCALE-ROBOT_R,-_sc->wm->oppRobot[i].pos.loc.y/WORLD_SCALE-ROBOT_R,ROBOT_D,ROBOT_D,Qt::AlignCenter,QString::number(i));
            }
    }

    // Draw Ball
    if(_sc->wm->ball.isValid)
    {
        painter.setPen(QColor::fromRgb(200,100,0));
        painter.setBrush(*brush_ball);
        painter.drawEllipse(QPoint(_sc->wm->ball.pos.loc.x/WORLD_SCALE,-_sc->wm->ball.pos.loc.y/WORLD_SCALE),BALL_R,BALL_R);
    }

    //painter.drawChord(100-ROBOT_R,100-ROBOT_R,ROBOT_D,ROBOT_D,ANGLE_TO_CHORD(0))
    //painter.drawText(100-ROBOT_R,100-ROBOT_R,ROBOT_D,ROBOT_D,Qt::AlignCenter,"8");

    _fps.Pulse();

    // Draw Navigation Positions
    if(_sc->wm->showAstarOut)
    {
        while( _sc->wm->navigation_pos.size() > 0 )
        {
            Vector2D point = _sc->wm->navigation_pos.takeFirst();
            painter.setPen(QColor::fromRgb(200,100,0));
            painter.setBrush(*brush_astarNode);
            painter.drawEllipse(QPoint(point.x/WORLD_SCALE,-point.y/WORLD_SCALE),NODE,NODE);
        }

        while( _sc->wm->navigation_result.size() > 0 )
        {
            Vector2D point = _sc->wm->navigation_result.takeFirst();
            painter.setPen(QColor::fromRgb(200,100,0));
            painter.setBrush(*brush_astarResult);
            painter.drawEllipse(QPoint(point.x/WORLD_SCALE,-point.y/WORLD_SCALE),NODE,NODE);
        }
    }

    //Draw Marking
    if( _sc->wm->showMarking )
    {
        for(int i=0;i<_sc->wm->marking.size();i++)
        {
            int ourIndex = _sc->wm->marking.at(i).ourI;
            QPoint our(_sc->wm->ourRobot[ourIndex].pos.loc.x/WORLD_SCALE , -_sc->wm->ourRobot[ourIndex].pos.loc.y/WORLD_SCALE);
            int oppIndex = _sc->wm->marking.at(i).oppI;
            QPoint opp(_sc->wm->oppRobot[oppIndex].pos.loc.x/WORLD_SCALE , -_sc->wm->oppRobot[oppIndex].pos.loc.y/WORLD_SCALE);

            painter.setPen(QColor::fromRgb(0,0,0));
            painter.setBrush(*brush_astarResult);
            painter.drawLine(our,opp);
        }
    }

    //Drawing Voronoi
    if(_sc->wm->showVoronoi)
    {
        for(int i=0;i<_sc->wm->voronoi.size();i++)
        {
            QPoint first(_sc->wm->voronoi.at(i).origin().x/WORLD_SCALE, -_sc->wm->voronoi.at(i).origin().y/WORLD_SCALE);
            QPoint second(_sc->wm->voronoi.at(i).terminal().x/WORLD_SCALE,-_sc->wm->voronoi.at(i).terminal().y/WORLD_SCALE);
            painter.setPen(QColor::fromRgb(0,0,0));
            painter.setBrush(*brush_astarResult);
            painter.drawLine(first,second);
        }
    }

    //Draw Pass Points
    if(_sc->wm->showPasses && (_sc->wm->passPoints.size() > 0) )
    {
        QPoint passTarget(_sc->wm->passPoints.at(0).x/WORLD_SCALE, -_sc->wm->passPoints.at(0).y/WORLD_SCALE);
        QPoint ball(_sc->wm->ball.pos.loc.x/WORLD_SCALE, -_sc->wm->ball.pos.loc.y/WORLD_SCALE);
        painter.setPen(QColor::fromRgb(125,125,0));
        painter.setBrush(*brush_pass);
        painter.drawLine(passTarget,ball);

        painter.setPen(QColor::fromRgb(125,125,0));
        painter.setBrush(*brush_pass);
        painter.drawEllipse(passTarget,BALL_R,BALL_R);
    }

    //Drawing debug points
    if(_sc->wm->showDebug)
    {
        if(_sc->wm->debug_type == 1)
        {
            for(int i=0;i<_sc->wm->debug_pos.size();i++)
            {
                QPoint point(_sc->wm->debug_pos.at(i).x/WORLD_SCALE, -_sc->wm->debug_pos.at(i).y/WORLD_SCALE);
                painter.setPen(QColor::fromRgb(255,0,0));
                painter.setBrush(*brush_debug);
                //painter.drawEllipse(point,BALL_R,BALL_R);
                painter.drawEllipse(point,1,1);
            }
        }
        else if(_sc->wm->debug_type == 2)
        {
            if( _sc->wm->debug_pos.size() > 0)
            {
                for(int i=0;i<_sc->wm->debug_pos.size()-1;i++)
                {
                    QPoint first(_sc->wm->debug_pos.at(i).x/WORLD_SCALE, -_sc->wm->debug_pos.at(i).y/WORLD_SCALE);
                    QPoint second(_sc->wm->debug_pos.at(i+1).x/WORLD_SCALE,-_sc->wm->debug_pos.at(i+1).y/WORLD_SCALE);
                    painter.setPen(QColor::fromRgb(255,0,0));
                    painter.setBrush(*brush_debug);

                    painter.drawEllipse(first,BALL_R,BALL_R);
                    painter.drawEllipse(second,BALL_R,BALL_R);
                    painter.drawLine(first,second);
                }

                QPoint first(_sc->wm->debug_pos.at(_sc->wm->debug_pos.size()-1).x/WORLD_SCALE, -_sc->wm->debug_pos.at(_sc->wm->debug_pos.size()-1).y/WORLD_SCALE);
                QPoint second(_sc->wm->debug_pos.at(0).x/WORLD_SCALE,-_sc->wm->debug_pos.at(0).y/WORLD_SCALE);
                painter.setPen(QColor::fromRgb(255,0,0));
                painter.setBrush(*brush_debug);

                painter.drawEllipse(first,BALL_R,BALL_R);
                painter.drawEllipse(second,BALL_R,BALL_R);
                painter.drawLine(first,second);
            }
        }
    }
    //    if(_sc->wm->selected.size()!=0)
    //    {
    //        QPoint first(_sc->wm->selected.at(0).x/WORLD_SCALE , -_sc->wm->selected.at(0).y/WORLD_SCALE);
    //        QPoint second(_sc->wm->selected.at(1).x/WORLD_SCALE , -_sc->wm->selected.at(1).y/WORLD_SCALE);
    //        QPoint third(_sc->wm->selected.at(2).x/WORLD_SCALE , -_sc->wm->selected.at(2).y/WORLD_SCALE);

    //        painter.setPen(QColor::fromRgb(50,50,50));
    //        painter.setBrush(*brush_astarResult);
    //        painter.drawLine(first,second);
    //        painter.drawLine(second,third);
    //        painter.drawLine(first,third);
    //    }
}
