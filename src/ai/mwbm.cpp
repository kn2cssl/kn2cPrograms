#include "mwbm.h"

MWBM::MWBM()
{
}

QList<int> MWBM::run(QList<int> input_weights, int numberOfVertex, bool &isMatched)
{
    igraph_t graph;
    igraph_vector_bool_t types;
    igraph_vector_long_t matching;
    igraph_vector_t weights;
    igraph_integer_t matching_size;
    igraph_real_t matching_weight;
    igraph_bool_t is_matching;

    QString ss;
    for(int i=0;i<input_weights.size();i++)
    {
        if(i%5 == 0)
            ss.append("\n");
        ss.append(QString::number(input_weights.at(i)));
        ss.append(",");
    }
    qDebug()<<ss;

    int i;
    QList<int> out;

    if(numberOfVertex == 3)
    {
        igraph_real_t weight_array[] =
        {    input_weights.at(0),input_weights.at(1),input_weights.at(2),
             input_weights.at(3),input_weights.at(4),input_weights.at(5),
             input_weights.at(6),input_weights.at(7),input_weights.at(8)
        };
        igraph_small(&graph,
                     0,0,
                     0,3, 0,4, 0,5,
                     1,3, 1,4, 1,5,
                     2,3, 2,4, 2,5,
                     -1);
        igraph_vector_bool_init(&types, 6);
        for (i = 0; i < 6; i++)
            VECTOR(types)[i] = (i >= 3);
        igraph_vector_long_init(&matching, 0);
        igraph_vector_init_copy(&weights, weight_array,
                                sizeof(weight_array) / sizeof(weight_array[0]));

        igraph_maximum_bipartite_matching(&graph, &types, &matching_size,
                                          &matching_weight, &matching, &weights, 0);

        igraph_is_maximal_matching(&graph, &types, &matching, &is_matching);
        if (!is_matching) {
            isMatched = false;
            qDebug()<<"Not Matched!!!";
        }
        else
        {
            isMatched = true;
            qDebug()<<"Matched.";
        }
    }
    else if(numberOfVertex == 4)
    {
        igraph_real_t weight_array[] =
        {    input_weights.at(0),input_weights.at(1),input_weights.at(2) ,input_weights.at(3),
             input_weights.at(4),input_weights.at(5),input_weights.at(6) ,input_weights.at(7),
             input_weights.at(8),input_weights.at(9),input_weights.at(10),input_weights.at(11),
             input_weights.at(12),input_weights.at(13),input_weights.at(14),input_weights.at(15)
        };
        igraph_small(&graph,
                     0,0,
                     0,4, 0,5, 0,6, 0,7,
                     1,4, 1,5, 1,6, 1,7,
                     2,4, 2,5, 2,6, 2,7,
                     3,4, 3,5, 3,6, 3,7,
                     -1);
        igraph_vector_bool_init(&types, 8);
        for (i = 0; i < 8; i++)
            VECTOR(types)[i] = (i >= 4);
        igraph_vector_long_init(&matching, 0);
        igraph_vector_init_copy(&weights, weight_array,
                                sizeof(weight_array) / sizeof(weight_array[0]));

        igraph_maximum_bipartite_matching(&graph, &types, &matching_size,
                                          &matching_weight, &matching, &weights, 0);

        igraph_is_maximal_matching(&graph, &types, &matching, &is_matching);
        if (!is_matching) {
            isMatched = false;
            qDebug()<<"Not Matched!!!";
        }
        else
        {
            isMatched = true;
            qDebug()<<"Matched.";
        }
    }
    else if(numberOfVertex == 5)
    {
        igraph_real_t weight_array[] =
        {    input_weights.at(0),input_weights.at(1),input_weights.at(2) ,input_weights.at(3),input_weights.at(4),
             input_weights.at(5),input_weights.at(6) ,input_weights.at(7),input_weights.at(8),input_weights.at(9),
             input_weights.at(10),input_weights.at(11),input_weights.at(12),input_weights.at(13),input_weights.at(14),
             input_weights.at(15),input_weights.at(16),input_weights.at(17),input_weights.at(18),input_weights.at(19),
             input_weights.at(20),input_weights.at(21),input_weights.at(22),input_weights.at(23),input_weights.at(24)
        };

        igraph_small(&graph,0,0,
                     0,5, 0,6, 0,7, 0,8, 0,9,
                     1,5, 1,6, 1,7, 1,8, 1,9,
                     2,5, 2,6, 2,7, 2,8, 2,9,
                     3,5, 3,6, 3,7, 3,8, 3,9,
                     4,5, 4,6, 4,7, 4,8, 4,9,
                     -1);
        igraph_vector_bool_init(&types, 10);
        for (i = 0; i < 10; i++)
            VECTOR(types)[i] = (i >= 5);
        igraph_vector_long_init(&matching, 0);
        igraph_vector_init_copy(&weights, weight_array,
                                sizeof(weight_array) / sizeof(weight_array[0]));

        igraph_maximum_bipartite_matching(&graph, &types, &matching_size,
                                          &matching_weight, &matching, &weights,DBL_EPSILON);

        igraph_is_maximal_matching(&graph, &types, &matching, &is_matching);
        if (!is_matching) {
            isMatched = false;
            qDebug()<<"Not Matched!!!";
        }
        else
        {
            isMatched=true;
            qDebug()<<"Matched.";
        }
    }

    for(int j=0;j<numberOfVertex*2;j++)
        out.append(VECTOR(matching)[j]);

    igraph_vector_destroy(&weights);
    igraph_vector_long_destroy(&matching);
    igraph_vector_bool_destroy(&types);
    igraph_destroy(&graph);

    return out;
}
