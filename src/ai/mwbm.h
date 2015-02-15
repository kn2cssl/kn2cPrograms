#ifndef MWBM_H
#define MWBM_H

#include <igraph/igraph.h>
#include <stdio.h>
#include <QList>
#include <QDebug>

class MWBM
{
public:
    MWBM();
    QList<int> run(QList<int> input_weights,int numberOfVertex);
};

#endif // MWBM_H
