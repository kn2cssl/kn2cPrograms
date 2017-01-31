#include "mantomandefense.h"

mantomanDefense::mantomanDefense(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest", worldmodel, parent)
{

}

int mantomanDefense::enterCondition()
{
    return 0;
}

void mantomanDefense::initRole()
{
}

void mantomanDefense::execute()
{

    QList <int> diffender = wm->kn->ActiveAgents();
    QList <int> enemy = wm->kn->ActiveOppAgents();
    QList <QList<double>> distances;
    for(int i = diffender.length() ; i > 0 ; i--){
        AlgorithmMin(diffender,enemy);
    }
}

void mantomanDefense::AlgorithmMin(QList<int>& enm,QList<int>& ally){
    QList <QList<double>> distances;
    for(int i = 0 ; i < ally.length() ; i++){
        QList<double> dists;
        for(int j = 0 ; j < enm.length() ; j++){
            Segment2D seg(wm->ourRobot[ally[i]].pos.loc,wm->oppRobot[enm[j]].pos.loc);
            std::cout << "i am here" << std::endl;
            dists.append(seg.length());
        }
        distances.append(dists);
    }

    double min = 99999999;
    int minIndex1 = 0;
    int minIndex2 = 0;
    for(int i = 0 ; i < ally.length() ; i++){
        for(int j = 0 ; j < enm.length() ; j++){
            if(distances[i][j] < min){
                min = distances[i][j];
                minIndex1 = i;
                minIndex2 = j;
            }
        }
    }
    tacticmantoman = new TacticTestStandingForwardEnemy(wm);
    tacticmantoman->setDistance(4);
    tacticmantoman->setOppRobotIndex(enm[minIndex2]);
    tactics[ally[minIndex1]] = tacticmantoman;
    ally.removeAt(minIndex1);
    enm.removeAt(minIndex2);
}
