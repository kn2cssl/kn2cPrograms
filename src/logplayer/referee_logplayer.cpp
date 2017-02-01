#include "referee_logplayer.h"

Referee_logPlayer::Referee_logPlayer(QObject *parent) :
    logPlayer(parent)
{
    qDebug()<<"Referee logPlayer Intialization...";

    elapsedTime = new QTime();
}

void Referee_logPlayer::playLog()
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

void Referee_logPlayer::loadLog(Ref_log logs)
{
    chunks.clear();
    this->frameNumber = 0;
    for(int i = 0; i < logs.chunks().size(); i++ )
    {
        chunks.append(logs.chunks(i));
    }
}

Ref_log Referee_logPlayer::saveLog()
{
    Ref_log logs;
    logs.set_number(this->counter);

    for(int i = 0; i < chunks.size(); i++)
    {
        Ref_chunk *chunk = logs.add_chunks();
        chunk->CopyFrom(chunks.at(i));
    }

    return logs;
}

void Referee_logPlayer::pauseLog()
{
    if( logIsPaused )
        QTimer::singleShot(15, this, SLOT(pauseLog()));
    emit dataReady();
}

void Referee_logPlayer::recordLog(SSL_Referee input)
{
    Ref_chunk chunk;
    chunk.set_id(this->counter);
    chunk.set_time_elapsed(elapsedTime->elapsed());
    SSL_Referee* packet(chunk.mutable_packet());
    packet->CopyFrom(input);
    chunks.append(chunk);
    this->counter++;
}

void Referee_logPlayer::restartTime()
{
    restartCounters();

    this->chunks.clear();
    this->elapsedTime->restart();
}

SSL_Referee Referee_logPlayer::returnCurrentPacket()
{
    return current_chunk.packet();
}

int Referee_logPlayer::getLength()
{
    if( !chunks.isEmpty() )
        return chunks.last().time_elapsed();

    return 0;
}

void Referee_logPlayer::setFrameNumber(int msec)
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

    if( Ub > Lb)
    {
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
    }

    if( foundIndex > 0)
    {
        this->current_chunk = chunks.at(foundIndex - 1);
        this->frameNumber = foundIndex;
        playLog();
    }
}

