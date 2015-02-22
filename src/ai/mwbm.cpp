#include "mwbm.h"

MWBM::MWBM()
{
}

QList<int> MWBM::run(QList<int> input_weights, int numberOfLeft, int numberOfRight, bool &isMatched)
{
    igraph_t graph;
    igraph_vector_bool_t types;
    igraph_vector_long_t matching;
    igraph_vector_t weights;
    igraph_integer_t matching_size;
    igraph_real_t matching_weight;
    igraph_bool_t is_matching;
    igraph_vector_t v;

    int i;
    QList<int> out;

    igraph_real_t weight_array[input_weights.size()];
    for(int j=0;j<input_weights.size();j++)
    {
        weight_array[j] = input_weights.at(j);
    };

    QList<int> edges_list;
    for(int j=0;j<numberOfLeft;j++)
    {
        for(int k=numberOfLeft;k<numberOfRight+numberOfLeft;k++)
        {
            edges_list.append(j);
            edges_list.append(k);
        }
    }

    igraph_real_t edges[edges_list.size()];

    for(int j=0;j<edges_list.size();j++)
    {
        edges[j] = edges_list.at(j);
    }

    igraph_vector_view(&v, edges, sizeof(edges)/sizeof(double));
    igraph_create(&graph, &v, 0, IGRAPH_DIRECTED);

    igraph_vector_bool_init(&types, numberOfLeft+numberOfRight);
    for (i = 0; i < numberOfLeft+numberOfRight; i++)
        VECTOR(types)[i] = (i >= numberOfLeft);
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

    for(int j=0;j<numberOfLeft*2;j++)
        out.append(VECTOR(matching)[j]);

    igraph_vector_destroy(&weights);
    igraph_vector_long_destroy(&matching);
    igraph_vector_bool_destroy(&types);
    igraph_destroy(&graph);

    return out;
}
