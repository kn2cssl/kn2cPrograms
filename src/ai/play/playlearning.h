#ifndef PLAYLEARNING_H
#define PLAYLEARNING_H

#include "play.h"

class PlayLearning : public Play
{
    Q_OBJECT
public:
    explicit PlayLearning(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    virtual void initRole();
    virtual int enterCondition();

private:
    TacticKickLearning* tKickLearner;
};

#endif // PLAYLEARNING_H
