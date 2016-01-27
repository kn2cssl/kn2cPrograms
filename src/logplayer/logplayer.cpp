#include "logplayer.h"

logPlayer::logPlayer(QString address, QObject *parent) :
    QObject(parent)
{
    this->counter = 0;
    this->address = address;
}

void logPlayer::setPlayPermission(bool input)
{
    this->playPermisssion = input;
}

void logPlayer::setPauseStatus(bool input)
{
    this->logIsPaused = input;
}
