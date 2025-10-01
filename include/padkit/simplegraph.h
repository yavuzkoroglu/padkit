#ifndef SIMPLE_GRAPH_H
    #define SIMPLE_GRAPH_H
    #include "padkit/graphmatrix.h"
    #include "padkit/indextable.h"

    typedef uint32_t Vertex;

    typedef struct EdgeBody {
        Vertex predecessor,
        Vertex successor
    } Edge;

    typedef SimpleGraphBody {
        ArrayList   vertex_list[1];
        ArrayList   vertex_label_id_list[1];
        ArrayList   adj_list[1];
    } SimpleGraph;

    void flush_graph(Graph* const graph);

    bool isValidEdge_graph(
        Graph* const graph,
        uint32_t const v0,
        uint32_t const v1
    );

    bool isValidVertex_graph(
        Graph* const graph,
        uint32_t const v
    );

    uint32_t insertVertex_graph(
        Graph* const graph,
        uint32_t const v_label,
    );

    uint32_t removeAllEdgesWithLabel_graph(
        Graph* const graph,
        uint32_t const e_label
    );

    uint32_t removeAllVerticesWithLabel_graph(
        Graph* const graph,
        uint32_t const v_label
    );

    void removeVertex_graph(
        Graph* const graph,
        uint32_t const v
    );

    #define GRAPH_MODE_SEARCH           (0)
    #define GRAPH_MODE_SEARCH_REMOVE    (1)
    #define GRAPH_MODE_INSERT_REPLACE   (2)
    #define GRAPH_MODE_INSERT_RESPECT   (3)
    #define GRAPH_MODE_FINAL            GRAPH_MODE_INSERT_RESPECT
    #define GRAPH_SEARCH_NOT_FOUND      (0)
    #define GRAPH_SEARCH_FOUND          (1)
    #define GRAPH_REPLACE_NO_CHANGES    (0)
    #define GRAPH_REPLACE_CHANGED       (1)
    #define GRAPH_RESPECT_NOT_UNIQUE    (0)
    #define GRAPH_RESPECT_UNIQUE        (1)
    #define GRAPH_REMOVE_NOT_FOUND      (0)
    #define GRAPH_REMOVE_FOUND          (1)
    uint32_t searchInsertEdgeLabel_graph(
        bool* const p_result,
        Graph const* const graph,
        uint32_t const v0,
        uint32_t const v1,
        uint32_t const e_label,
        uint32_t const mode
    );
#endif
