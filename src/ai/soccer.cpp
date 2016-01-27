#include "soccer.h"

Soccer::Soccer(QObject *parent) :
    QObject(parent)
{
    qDebug() << "Soccer Initialization...";
    Settings s("settings.ini");

    QString gm = s.Get("Game","Mode");
    log += "Mode : " + gm + "\n\n";

    QString rip = s.Get(gm, "RefIP");
    log += "RefIP : " + rip + "\n";

    field = s.Get("Field","Size");
    log += "Field Size : "+ field + "\n";
    qDebug()<<"field : "<<field;

    int rport = s.Get(gm, "RefPort").toInt();
    log += "RefPort : " + QString::number(rport) + "\n";

    int rportn = s.Get(gm, "RefPortNew").toInt();
    log += "RefPortNew : " + QString::number(rportn) + "\n";

    float ball_dist = s.Get("RefereeConfig", "RefereeBall").toFloat();
    log += "RefereeBall : " + QString::number(ball_dist) + "\n\n";

    QString vip = s.Get(gm, "VisionIP");
    log += "VisionIP : " + rip + "\n";

    int vport = s.Get(gm, "VisionPort").toInt();
    log += "VisionPort : " + QString::number(vport) + "\n\n";

    QString scolor = s.Get("Team","Color");
    log += "Color : " + scolor + "\n\n";
    TeamColorType tcolor = (scolor=="Blue")?COLOR_BLUE:COLOR_YELLOW;

    QString sside = s.Get("Team","Side");
    log += "Side : " + sside + "\n\n";
    TeamSideType tside = (sside=="Right")?SIDE_RIGHT:SIDE_LEFT;

    CameraConfigType tcam = (CameraConfigType)s.Get("VisionConfig","UsingCameras").toInt();
    log += "UsingCameras : " + QString::number(tcam) + "\n\n";

    QString simip = s.Get("grSim", "CommandIP");
    log += "grSim CommandIP : " + simip + "\n";

    int simport = s.Get("grSim", "CommandPort").toInt();
    log += "grSim CommandPort : " + QString::number(simport) + "\n\n";

    QString serialport = s.Get("Transmitter","SerialPort");
    log += "SerialPort : " + serialport + "\n\n";


    // Game mode
    gamemode = (gm=="Simulation")?MODE_SIMULATION:MODE_REAL;
    qDebug() << "Game mode: " << gm << "\n";

    // output buffer
    outputbuffer = new OutputBuffer;

    // Vison & referee
    wm = new WorldModel(outputbuffer);
    wm->ourColor = tcolor;
    MapSearchNode::wm = wm;
    if( field == "Double" )
        sslvision = new SSLVision_Double(vip, vport, tcolor, tside, tcam, wm);
    else
        sslvision = new SSLVision_Single(vip, vport, tcolor, tside, tcam, wm);

    sslvision->Start();

    sslrefbox = 0;
    sslrefboxnew = 0;

    int refusenew = s.Get(gm, "RefUseNew").toInt();
    if(refusenew == 1)
    {
        sslrefboxnew = new SSLRefBoxNew(rip, rportn, tcolor, ball_dist, wm);
        sslrefboxnew->Start();
    }
    else
    {
        sslrefbox = new SSLRefBox(rip, rport, tcolor, ball_dist, wm);
        sslrefbox->Start();
    }

    // manual Referee
    sslrefbox2 = 0;
    sslrefboxnew2 = 0;

    QString mren = s.Get("ManualRef", "Enable");
    QString mrip = s.Get("ManualRef", "RefIP");
    int mrport = s.Get("ManualRef", "RefPort").toInt();
    int mrportn = s.Get("ManualRef", "RefPortNew").toInt();
    int mrefusenew = s.Get("ManualRef", "RefUseNew").toInt();

    if(mren.toInt() == 1)
    {
        log += "Manual RefIP : " + mrip + "\n";
        log += "Manual RefPort : " + QString::number(mrport) + "\n";
        log += "Manual RefPortNew : " + QString::number(mrportn) + "\n";

        if(mrefusenew == 1)
        {
            sslrefboxnew2 = new SSLRefBoxNew(mrip, mrportn, tcolor, ball_dist, wm);
            sslrefboxnew2->paused = true;
            sslrefboxnew2->Start();
        }
        else
        {
            sslrefbox2 = new SSLRefBox(mrip, mrport, tcolor, ball_dist, wm);
            sslrefbox2->paused = true;
            sslrefbox2->Start();
        }
    }
    else
    {
        log += "ManualRef Disabled \n";
    }

    // grSim
    grsim = 0;
    if(gamemode==MODE_SIMULATION)
    {
        grsim = new grSim(simip, simport, tcolor, outputbuffer);
        grsim->Start();
        wm->isSim = true;
    }

    // serial port transmitter
    transmitter = 0;
    if(gamemode==MODE_REAL)
    {
        transmitter = new Transmitter(serialport, outputbuffer, wm);
        transmitter->Start();
        wm->isSim = false;
    }

    // AI
    ai = new AI(wm, field,outputbuffer, this);
    ai->Start();
}

void Soccer::recordGameLog()
{
    sslvision->startRecording();
    ai->startRecording();
}

void Soccer::stopGameLog()
{
    sslvision->stopPlaying();
    ai->stopPlaying();
}

bool Soccer::saveGameLog()
{
    logRecord logs;

    Vision_log* visionLogs(logs.mutable_vision());
    visionLogs->CopyFrom(sslvision->stopRecording());

    SSL_log* aiLogs(logs.mutable_ai());
    aiLogs->CopyFrom(ai->stopRecording());

    QString logName;// = address;
    logName.append("Log");
    logName.append(QString::number(QDateTime::currentDateTime().date().year()));
    logName.append(QString::number(QDateTime::currentDateTime().date().month()));
    logName.append(QString::number(QDateTime::currentDateTime().date().day()));
    logName.append("_");
    logName.append(QString::number(QDateTime::currentDateTime().time().hour()));
    logName.append(":");
    logName.append(QString::number(QDateTime::currentDateTime().time().minute()));
    logName.append(":");
    logName.append(QString::number(QDateTime::currentDateTime().time().second()));
    logName.append(".txt");

    QFile file(logName);
    this->Address = logName;

    if( !file.exists() )
    {
        if ( file.open(QIODevice::WriteOnly | QIODevice::Text) )
        {
            fstream output;
            output.open(logName.toUtf8(), fstream::out | fstream::trunc | fstream::binary);;
            if ( logs.SerializeToOstream(&output) )
            {
                qDebug() << "Log saved compleltely." << endl;
                return true;
            }
        }
    }

    return false;
}

void Soccer::playGameLog()
{
    sslvision->startPlaying();
    ai->startPlaying();
}

void Soccer::pauseGameLog()
{
    sslvision->pausePlaying();
    ai->pausePlaying();
}

void Soccer::loadGameLog()
{
    logRecord logs;

    fstream input;
    input.open(Address.toUtf8(), ios::in | ios::binary);
    if (!input)
    {
        qDebug() << Address << ": File not found.  Creating a new file." << endl;

    }
    else if (!logs.ParseFromIstream(&input))
    {
        qDebug() << "Failed";
    }
    else
    {
        sslvision->loadPlaying(logs.vision());
    }
}

void Soccer::loadGameLog(QString address)
{
    logRecord logs;

    fstream input;
    input.open(address.toUtf8(), ios::in | ios::binary);
    if (!input)
    {
        qDebug() << address << ": File not found.  Creating a new file." << endl;

    }
    else if (!logs.ParseFromIstream(&input))
    {
        qDebug() << "Failed";
    }
    else
    {
        qDebug()<<"vision is valid? "<<logs.vision().IsInitialized();
        sslvision->loadPlaying(logs.vision());
        qDebug()<<"ai is valid? "<<logs.ai().IsInitialized();
        ai->loadPlaying(logs.ai());
    }
}

int Soccer::logLength()
{
    int max;

    max = sslvision->logLength();

    return max;
}

void Soccer::setLogFrame(int msec)
{
    sslvision->setLogFrame(msec);
}
