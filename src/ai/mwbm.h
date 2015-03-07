#ifndef MWBM_H
#define MWBM_H

#include <igraph/igraph.h>
#include <float.h>
#include <stdio.h>
#include <QList>
#include <QDebug>

class MWBM
{
public:
    MWBM();
    QList<int> run(QList<int> input_weights,int numberOfLeft,int numberOfRight,bool &isMatched);
};

#endif // MWBM_H
