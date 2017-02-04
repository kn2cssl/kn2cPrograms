#include "sslvision.h"

SSLVision::SSLVision(QString ip, int port, TeamColorType color, TeamSideType side, CameraConfigType camera, WorldModel *wm, QObject *parent) :
    SSLReceiver(ip,port,parent),
    _color(color),
    _side(side),
    _camera(camera),
    _wm(wm)
{
    qRegisterMetaType<SSL_WrapperPacket>("SSL_WrapperPacket");

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
    int CamId = pck.camera_id() % CAMERA_NUM;
    _fpscam[CamId].Pulse();

    // update vision frame
    //_vframe[cid].frame_number =  pck.frame_number();

    // Team side Coefficient
    float ourSide = (_side == SIDE_RIGHT)? -1.0f : 1.0f;
    time = pck.t_capture()*1000;

    // insert balls
    for(int i=0; i < pck.balls_size(); ++i)
    {
        auto b = pck.balls(i);
        PositionTimeCamera point;
        point.pos.loc = Vector2D(b.x()*ourSide, b.y()*ourSide);
        point.confidence = b.confidence();
        point.camera =  CamId;
        point.time = time;
        balls.push_back(point);
    }
    //insert robots
    if(_color == COLOR_BLUE)
    {
        for (int i = 0 ; i < pck.robots_blue_size() ; i++)
        {
            int robotId = pck.robots_blue(i).robot_id();
            addRobot(pck.robots_blue(i),robotId,false,time,CamId);
        }
        for (int i = 0 ; i < pck.robots_yellow_size() ; i++)
        {
            int robotId = pck.robots_blue(i).robot_id();
            addRobot(pck.robots_yellow(i),robotId,true,time,CamId);
        }
    }
    else
    {
        for (int i = 0 ; i < pck.robots_yellow_size(); i++)
        {
            int robotId = pck.robots_blue(i).robot_id();
            addRobot(pck.robots_yellow(i),robotId,false,time,CamId);
        }
        for (int i = 0 ; i < pck.robots_blue_size() ; i++)
        {
            int robotId = pck.robots_blue(i).robot_id();
            addRobot(pck.robots_blue(i),robotId,true,time,CamId);
        }
    }

    checkCameras[CamId] = true;
    if((checkCameras[1] & checkCameras[2]) == true && time > 4){
        for(int i = 0 ; i < 5 ; i++)
            checkCameras[i] = false;
        _wm->ball.seenAt(balls);
        qDebug() << "i am here";
        balls.clear();
        for (int i = 0; i < PLAYERS_MAX_NUM; ++i) {
            _wm->ourRobot[i].seenAt(ourRobots[i]);
            _wm->oppRobot[i].seenAt(oppRobots[i]);
            ourRobots[i].clear();
            oppRobots[i].clear();
        }
    }
}

void SSLVision::parseLog(SSL_DetectionFrame &pck)
{
}

void SSLVision::addRobot(const SSL_DetectionRobot& robot,int id,bool isEnemy,double time,int camera){
    float ourSide = (_side == SIDE_RIGHT)? -1.0f : 1.0f;
    PositionTimeCamera point;
    point.pos.loc = Vector2D(robot.x()*ourSide, robot.y()*ourSide);
    point.pos.dir = robot.orientation()+(1.0 - ourSide)*M_PI_2;
    point.confidence = robot.confidence();
    point.camera = camera;
    point.time = time;
    if(point.pos.dir > M_PI)
        point.pos.dir -= M_2PI;
    if(isEnemy)
        oppRobots[id].push_back(point);
    else
        ourRobots[id].push_back(point);
}
