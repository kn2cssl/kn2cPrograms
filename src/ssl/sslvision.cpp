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

    logplayer = new Vision_logPlayer(wm, "test",parent);
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

void SSLVision::stopRecording()
{
    recordPermission = false;
    logplayer->saveLog();
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

void SSLVision::loadPlaying(QString address)
{
    logplayer->loadLog(address);
}

int SSLVision::logLength()
{
    return logplayer->getLength();
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
