#include "sslvision.h"

SSLVision::SSLVision(QString ip, int port, TeamColorType color, TeamSideType side, CameraConfigType camera, WorldModel *wm, QObject *parent) :
    SSLReceiver(ip,port,parent),
    _color(color),
    _side(side),
    _camera(camera),
    _wm(wm)
{
    qRegisterMetaType<SSL_WrapperPacket>("SSL_WrapperPacket");

    _time.start();
    connect(this, SIGNAL(newReceivedPacket(QByteArray,QString,int)), this, SLOT(readPendingPacket(QByteArray,QString,int)),Qt::DirectConnection);

    logplayer = new Vision_logPlayer();
    recordPermission = false;

    connect(logplayer, SIGNAL(dataReady()), this, SLOT(logResponder()));

    // Log
    qDebug() << "SSLVision Initialization...";
    qDebug() << "IP: " << ip;
    qDebug() << "Port: " << port;
    qDebug() << "Color: " << (color==COLOR_BLUE?"Blue":"Yellow");
    qDebug() << "Side: " << (side==SIDE_RIGHT?"Right":"Left");
    qDebug() << "Camera: " << ((int)camera);
}

void SSLVision::startRecording()
{
    recordPermission = true;
    logplayer->restartTime();
}

Vision_log SSLVision::stopRecording()
{
    recordPermission = false;
    return logplayer->saveLog();
}

void SSLVision::startPlaying()
{
    this->Stop();
    logplayer->setPlayPermission(true);
    logplayer->setPauseStatus(false);
    logplayer->playLog();
}

void SSLVision::stopPlaying()
{
    logplayer->setPlayPermission(false);
    logplayer->setPauseStatus(false);
    this->Start();
}

void SSLVision::pausePlaying()
{
    logplayer->setPlayPermission(false);
    logplayer->setPauseStatus(true);
    logplayer->pauseLog();
}

void SSLVision::loadPlaying(Vision_log logs)
{
    logplayer->loadLog(logs);
}

int SSLVision::logLength()
{
    return logplayer->getLength();
}

void SSLVision::setLogFrame(int msec)
{
   logplayer->setFrameNumber(msec);
}

void SSLVision::readPendingPacket(QByteArray data, QString ip, int port)
{
    // check for server ip (& port)
    if(ip=="" && port==0) return;

    // unpack sslvision packet
    SSL_WrapperPacket packet;
    bool ans=packet.ParseFromArray(data.data(), data.size());
    if(!ans) return;
    if(packet.has_detection()==false) return;
    SSL_DetectionFrame pck = packet.detection();

    //Record gameLogs
    if( recordPermission )
        logplayer->recordLog(packet);

    // parse detection frame
    parse(pck);
}

void SSLVision::logResponder()
{
    SSL_WrapperPacket packet = logplayer->returnCurrentPacket();

    if(! packet.IsInitialized() ) return;
    if(packet.has_detection()==false) return;
    SSL_DetectionFrame pck = packet.detection();

    // parse detection frame
    parseLog(pck);
}
int SSLVision::getFPS(int c)
{
    return (c % CAMERA_NUM);
}

void SSLVision::parse(SSL_DetectionFrame &pck)
{
    // update camera fps
    int cid = pck.camera_id() % CAMERA_NUM;
    _fpscam[cid].Pulse();

    // update vision frame
    //_vframe[cid].frame_number =  pck.frame_number();

    vector<Position> pt;

    // Team side Coefficient
    float ourSide = (_side == SIDE_RIGHT)? -1.0f : 1.0f;
    qDebug() << "capture" << pck.t_capture()*1000 - time;
    time = pck.t_capture()*1000;

    // insert balls
    int max_balls=min(VOBJ_MAX_NUM, pck.balls_size());
    for(int i=0; i<max_balls; ++i)
    {
        auto b = pck.balls(i);
        if(b.has_confidence() && b.has_x() && b.has_y())
            if(b.confidence() > MIN_CONF && fabs(b.x()) < FIELD_DOUBLE_MAX_X && fabs(b.y()) < FIELD_DOUBLE_MAX_Y)
//            if(b.confidence() > MIN_CONF && (fabs(b.x()) < FIELD_MAX_X && fabs(b.x()) > 600) && fabs(b.y()) < FIELD_MAX_Y)
            {
                Position tp;
                tp.loc = Vector2D(b.x()*ourSide, b.y()*ourSide);
                pt.push_back(tp);
            }
    }
    _wm->ball.seenAt(pt, time, cid);

    if(_color == COLOR_BLUE)
    {
        for (int i=0; i<pck.robots_blue_size(); ++i)
        {
            pt.clear();
            int rid = pck.robots_blue(i).robot_id();
            if ((pck.robots_blue(i).has_orientation())&&(pck.robots_blue(i).has_confidence())&&(pck.robots_blue(i).confidence()>MIN_CONF)&&(fabs(pck.robots_blue(i).x())<FIELD_DOUBLE_MAX_X /*&& fabs(pck.robots_##__COLOR__(i).x())>600*/)&&(fabs(pck.robots_blue(i).y())<FIELD_DOUBLE_MAX_Y))
            {
                Position tp;
                tp.loc = Vector2D(pck.robots_blue(i).x()*ourSide, pck.robots_blue(i).y()*ourSide);
                tp.dir = pck.robots_blue(i).orientation()+(1.0-ourSide)*M_PI_2;
                if(tp.dir>M_PI) tp.dir -= M_2PI;
                pt.push_back(tp);
                _wm->ourRobot[rid].seenAt(pt, time, cid);
            }
        }
        for (int i=0; i<pck.robots_yellow_size(); ++i)
        {
            pt.clear();
            int rid = pck.robots_yellow(i).robot_id();
            if ((pck.robots_yellow(i).has_orientation())&&(pck.robots_yellow(i).has_confidence())&&(pck.robots_yellow(i).confidence()>MIN_CONF)&&(fabs(pck.robots_yellow(i).x())<FIELD_DOUBLE_MAX_X /*&& fabs(pck.robots_##__COLOR__(i).x())>600*/)&&(fabs(pck.robots_yellow(i).y())<FIELD_DOUBLE_MAX_Y))
            {
                Position tp;
                tp.loc = Vector2D(pck.robots_yellow(i).x()*ourSide, pck.robots_yellow(i).y()*ourSide);
                tp.dir = pck.robots_yellow(i).orientation()+(1.0-ourSide)*M_PI_2;
                if(tp.dir>M_PI) tp.dir -= M_2PI;
                pt.push_back(tp);
                _wm->oppRobot[rid].seenAt(pt, time, cid);
            }
        }
    }
    else
    {
        for (int i=0; i<pck.robots_yellow_size(); ++i)
        {
            pt.clear();
            int rid = pck.robots_yellow(i).robot_id();
            if ((pck.robots_yellow(i).has_orientation())&&(pck.robots_yellow(i).has_confidence())&&(pck.robots_yellow(i).confidence()>MIN_CONF)&&(fabs(pck.robots_yellow(i).x())<FIELD_DOUBLE_MAX_X /*&& fabs(pck.robots_yellow(i).x())>600*/)&&(fabs(pck.robots_yellow(i).y())<FIELD_DOUBLE_MAX_Y))
            {
                Position tp;
                tp.loc = Vector2D(pck.robots_yellow(i).x()*ourSide, pck.robots_yellow(i).y()*ourSide);
                tp.dir = pck.robots_yellow(i).orientation()+(1.0-ourSide)*M_PI_2;
                if(tp.dir>M_PI) tp.dir -= M_2PI;
                pt.push_back(tp);
                _wm->ourRobot[rid].seenAt(pt, time, cid);
            }
        }
        for (int i=0; i<pck.robots_blue_size(); ++i)
        {
            pt.clear();
            int rid = pck.robots_blue(i).robot_id();
            if ((pck.robots_blue(i).has_orientation())&&(pck.robots_blue(i).has_confidence())&&(pck.robots_blue(i).confidence()>MIN_CONF)&&(fabs(pck.robots_blue(i).x())<FIELD_DOUBLE_MAX_X /*&& fabs(pck.robots_##__COLOR__(i).x())>600*/)&&(fabs(pck.robots_blue(i).y())<FIELD_DOUBLE_MAX_Y))
            {
                Position tp;
                tp.loc = Vector2D(pck.robots_blue(i).x()*ourSide, pck.robots_blue(i).y()*ourSide);
                tp.dir = pck.robots_blue(i).orientation()+(1.0-ourSide)*M_PI_2;
                if(tp.dir>M_PI) tp.dir -= M_2PI;
                pt.push_back(tp);
                _wm->oppRobot[rid].seenAt(pt, time, cid);
            }
        }
    }
}

void SSLVision::parseLog(SSL_DetectionFrame &pck)
{
    // update camera fps
    int cid = pck.camera_id();

    switch(_camera)
    {
    case CAMERA_ALL:
        break;
    case CAMERA_0:
        if (cid==1 || cid==2 || cid==3) return;
        break;
    case CAMERA_1:
        if (cid==0 || cid==2 || cid==3) return;
        break;
    case CAMERA_2:
        if (cid==0 || cid==1 || cid==3) return;
        break;
    case CAMERA_3:
        if (cid==0 || cid==1 || cid==2) return;
        break;
    case CAMERA_BOTH_L:
        if (cid==2 || cid==3) return;
        break;
    case CAMERA_BOTH_R:
        if (cid==0 || cid==1) return;
        break;
    case CAMERA_NONE:
    default:
        return;
    }

    // update vision frame
    //_vframe[cid].frame_number =  pck.frame_number();

    vector<Position> pt;

    // Team side Coefficient
    float ourSide = (_side == SIDE_RIGHT)? -1.0f : 1.0f;
    double time = _time.elapsed(); //pck.t_capture();

    // insert balls
    int max_balls=min(VOBJ_MAX_NUM, pck.balls_size());
    for(int i=0; i<max_balls; ++i)
    {
        auto b = pck.balls(i);
        if(b.has_confidence() && b.has_x() && b.has_y())
            if(b.confidence() > MIN_CONF && fabs(b.x()) < FIELD_DOUBLE_MAX_X && fabs(b.y()) < FIELD_DOUBLE_MAX_Y)
//            if(b.confidence() > MIN_CONF && (fabs(b.x()) < FIELD_MAX_X && fabs(b.x()) > 600) && fabs(b.y()) < FIELD_MAX_Y)
            {
                Position tp;
                tp.loc = Vector2D(b.x()*ourSide, b.y()*ourSide);
                pt.push_back(tp);
            }
    }
    _wm->ball.seenAt(pt, time, cid);

    if(_color == COLOR_BLUE)
    {
        for (int i=0; i<pck.robots_blue_size(); ++i)
        {
            pt.clear();
            int rid = pck.robots_blue(i).robot_id();
            if ((pck.robots_blue(i).has_orientation())&&(pck.robots_blue(i).has_confidence())&&(pck.robots_blue(i).confidence()>MIN_CONF)&&(fabs(pck.robots_blue(i).x())<FIELD_DOUBLE_MAX_X /*&& fabs(pck.robots_##__COLOR__(i).x())>600*/)&&(fabs(pck.robots_blue(i).y())<FIELD_DOUBLE_MAX_Y))
            {
                Position tp;
                tp.loc = Vector2D(pck.robots_blue(i).x()*ourSide, pck.robots_blue(i).y()*ourSide);
                tp.dir = pck.robots_blue(i).orientation()+(1.0-ourSide)*M_PI_2;
                if(tp.dir>M_PI) tp.dir -= M_2PI;
                pt.push_back(tp);
                _wm->ourRobot[rid].seenAt(pt, time, cid);
            }
        }
        for (int i=0; i<pck.robots_yellow_size(); ++i)
        {
            pt.clear();
            int rid = pck.robots_yellow(i).robot_id();
            if ((pck.robots_yellow(i).has_orientation())&&(pck.robots_yellow(i).has_confidence())&&(pck.robots_yellow(i).confidence()>MIN_CONF)&&(fabs(pck.robots_yellow(i).x())<FIELD_DOUBLE_MAX_X /*&& fabs(pck.robots_##__COLOR__(i).x())>600*/)&&(fabs(pck.robots_yellow(i).y())<FIELD_DOUBLE_MAX_Y))
            {
                Position tp;
                tp.loc = Vector2D(pck.robots_yellow(i).x()*ourSide, pck.robots_yellow(i).y()*ourSide);
                tp.dir = pck.robots_yellow(i).orientation()+(1.0-ourSide)*M_PI_2;
                if(tp.dir>M_PI) tp.dir -= M_2PI;
                pt.push_back(tp);
                _wm->oppRobot[rid].seenAt(pt, time, cid);
            }
        }
    }
    else
    {
        for (int i=0; i<pck.robots_yellow_size(); ++i)
        {
            pt.clear();
            int rid = pck.robots_yellow(i).robot_id();
            if ((pck.robots_yellow(i).has_orientation())&&(pck.robots_yellow(i).has_confidence())&&(pck.robots_yellow(i).confidence()>MIN_CONF)&&(fabs(pck.robots_yellow(i).x())<FIELD_DOUBLE_MAX_X /*&& fabs(pck.robots_yellow(i).x())>600*/)&&(fabs(pck.robots_yellow(i).y())<FIELD_DOUBLE_MAX_Y))
            {
                Position tp;
                tp.loc = Vector2D(pck.robots_yellow(i).x()*ourSide, pck.robots_yellow(i).y()*ourSide);
                tp.dir = pck.robots_yellow(i).orientation()+(1.0-ourSide)*M_PI_2;
                if(tp.dir>M_PI) tp.dir -= M_2PI;
                pt.push_back(tp);
                _wm->ourRobot[rid].seenAt(pt, time, cid);
            }
        }
        for (int i=0; i<pck.robots_blue_size(); ++i)
        {
            pt.clear();
            int rid = pck.robots_blue(i).robot_id();
            if ((pck.robots_blue(i).has_orientation())&&(pck.robots_blue(i).has_confidence())&&(pck.robots_blue(i).confidence()>MIN_CONF)&&(fabs(pck.robots_blue(i).x())<FIELD_DOUBLE_MAX_X /*&& fabs(pck.robots_##__COLOR__(i).x())>600*/)&&(fabs(pck.robots_blue(i).y())<FIELD_DOUBLE_MAX_Y))
            {
                Position tp;
                tp.loc = Vector2D(pck.robots_blue(i).x()*ourSide, pck.robots_blue(i).y()*ourSide);
                tp.dir = pck.robots_blue(i).orientation()+(1.0-ourSide)*M_PI_2;
                if(tp.dir>M_PI) tp.dir -= M_2PI;
                pt.push_back(tp);
                _wm->oppRobot[rid].seenAt(pt, time, cid);
            }
        }
    }
}
