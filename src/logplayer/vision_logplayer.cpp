#include "vision_logplayer.h"

Vision_logPlayer::Vision_logPlayer(QObject *parent) :
    logPlayer(parent)
{
    qDebug()<<"Vision logPlayer Intialization...";

    elapsedTime = new QTime();
}

void Vision_logPlayer::playLog()
{
    if( frameNumber < chunks.size() )
    {
        int lastTime = (frameNumber == 0) ? 0 : current_chunk.time_elapsed();
        current_chunk = chunks.at(frameNumber++);
        if( playPermisssion )
            QTimer::singleShot(current_chunk.time_elapsed()-lastTime, this, SLOT(playLog()));
        emit dataReady();
    }
}

void Vision_logPlayer::loadLog(Vision_log logs)
{
    chunks.clear();
    this->frameNumber = 0;
    for(int i = 0; i < logs.chunks().size(); i++ )
    {
        chunks.append(logs.chunks(i));
    }
}

Vision_log Vision_logPlayer::saveLog()
{
    Vision_log logs;
    logs.set_number(this->counter);

    for(int i = 0; i < chunks.size(); i++)
    {
        Vision_chunk *chunk = logs.add_chunks();
        chunk->CopyFrom(chunks.at(i));
    }

    return logs;
}

void Vision_logPlayer::pauseLog()
{
    if( logIsPaused )
        QTimer::singleShot(15, this, SLOT(pauseLog()));
    emit dataReady();
}

void Vision_logPlayer::recordLog(SSL_WrapperPacket input)
{
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
    restartCounters();

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

void Vision_logPlayer::setFrameNumber(int msec)
{
    //    int function BinarySearch (Array A, int Lb, int Ub, int Key);
    //      begin
    //      do forever
    //        M = (Lb + Ub)/2;
    //        if (Key < A[M]) then
    //          Ub = M - 1;
    //        else if (Key > A[M]) then
    //          Lb = M + 1;
    //        else
    //          return M;
    //        if (Lb > Ub) then
    //          return -1;
    //      end;
    
    int Lb, Ub, Mid, foundIndex = -1;
    Lb = 0; Ub = chunks.size();

    do
    {
        Mid = (Lb + Ub)/2;

        if ( msec - chunks.at(Mid).time_elapsed() < -10 )
            Ub = Mid - 1;
        else if ( msec - chunks.at(Mid).time_elapsed() > 10 )
            Lb = Mid + 1;
        else
        {
            foundIndex = Mid;
            break;
        }
    }
    while( Lb < Ub );

    if( foundIndex >= 0)
    {
        this->current_chunk = chunks.at(foundIndex - 1);
        this->frameNumber = foundIndex;
        playLog();
    }
}
