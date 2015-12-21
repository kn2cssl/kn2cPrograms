#include "logplayer.h"

logPlayer::logPlayer(QString address, QObject *parent) :
    QObject(parent)
{
    this->counter = 0;
    this->address = address;
}
