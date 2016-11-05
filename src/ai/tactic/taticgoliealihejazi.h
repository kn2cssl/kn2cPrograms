#ifndef TATICGOLIEALIHEJAZI_H
#define TATICGOLIEALIHEJAZI_H
#include "tactic.h"

class taticgoliealihejazi : public Tactic
{
    Q_OBJECT
public:
    explicit taticgoliealihejazi(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
};

#endif // TATICGOLIEALIHEJAZI_H
