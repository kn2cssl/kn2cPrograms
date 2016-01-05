#include "vision_logplayer.h"

Vision_logPlayer::Vision_logPlayer(WorldModel *worldmodel, QString address, QObject *parent) :
    logPlayer(address,parent),
    wm(worldmodel)
{
    qDebug()<<"Vision logPlayer Intialization...";
    qDebug()<<"Address: "<<address;

    elapsedTime = new QTime();
    playPermisssion = false;

}

void Vision_logPlayer::playLog()
{
    if( !chunks.isEmpty() )
    {
        current_chunk = chunks.takeFirst();
        QTimer::singleShot(current_chunk.time_elapsed(), this, SLOT(timerShot()));
        emit dataReady();
    }
}

bool Vision_logPlayer::loadLog()
{
    Vision_log logs;

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
        chunks.clear();
        for(int i = 0; i < logs.chunks().size(); i++ )
        {
            chunks.append(logs.chunks(i));
        }
    }
}

bool Vision_logPlayer::loadLog(QString address)
{
    Vision_log logs;

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
        chunks.clear();
        for(int i = 0; i < logs.chunks().size(); i++ )
        {
            chunks.append(logs.chunks(i));
        }
    }
}

bool Vision_logPlayer::saveLog()
{
    Vision_log logs;
    logs.set_number(this->counter);

    for(int i = 0; i < chunks.size(); i++)
    {
        Vision_chunk *chunk = logs.add_chunks();
        chunk->CopyFrom(chunks.at(i));
    }

    QString logName = address;
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
    this->address = logName;

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

void Vision_logPlayer::recordLog(SSL_WrapperPacket input)
{
    qDebug()<<"record log";
    Vision_chunk chunk;
    chunk.set_id(this->counter);
    chunk.set_time_elapsed(elapsedTime->elapsed());
    SSL_WrapperPacket* packet(chunk.mutable_packet());
    packet->CopyFrom(input);
    chunks.append(chunk);
    this->counter++;
}

void Vision_logPlayer::restartTime()
{
    this->counter = 0;
    this->chunks.clear();
    this->elapsedTime->restart();
}

SSL_WrapperPacket Vision_logPlayer::returnCurrentPacket()
{
    return current_chunk.packet();
}

int Vision_logPlayer::getLength()
{
    if( !chunks.isEmpty() )
        return chunks.last().time_elapsed();

    return 0;
}

void Vision_logPlayer::setPlayPermission(bool input)
{
    this->playPermisssion = input;
}

void Vision_logPlayer::timerShot()
{
    if( !chunks.isEmpty() )
    {
        int lastTime = current_chunk.time_elapsed();
        current_chunk = chunks.takeFirst();
        if( playPermisssion )
            QTimer::singleShot(current_chunk.time_elapsed()-lastTime, this, SLOT(timerShot()));
        emit dataReady();
    }
}

