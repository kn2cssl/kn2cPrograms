#ifndef MANTOMANDEFENSE_H
#define MANTOMANDEFENSE_H
#include "play.h"
#include "man2man.h"

class mantomanDefense : public Play
{
    Q_OBJECT
public:
    explicit mantomanDefense(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    virtual void initRole();
    virtual int enterCondition();
private:
    TacticTestStandingForwardEnemy* tacticmantoman;
    void AlgorithmMin(QList<int>& enm, QList<int>& ally);
};

#endif // MANTOMANDEFENSE_H
