#include "logplayer.h"

logPlayer::logPlayer(QObject *parent) :
    QObject(parent)
{
    this->counter = 0;
    this->playPermisssion = false;
    this->logIsPaused = false;
    this->frameNumber = 0;
}

void logPlayer::setPlayPermission(bool input)
{
    this->playPermisssion = input;
}

void logPlayer::setPauseStatus(bool input)
{
    this->logIsPaused = input;
}

void logPlayer::restartCounters()
{
    this->counter = 0;
    this->frameNumber = 0;
}
