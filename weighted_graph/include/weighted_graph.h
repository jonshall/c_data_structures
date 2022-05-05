/**
 * @file   weighted_graph.h
 * @author Jon S Hall
 * @brief  weighted graph
 * @date   December 2021
 */

#ifndef _WEIGHTED_GRAPH_H
#define _WEIGHTED_GRAPH_H

#include <limits.h>
#include <queue.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// debug print
#ifdef DEBUG
#define debug_print(x) printf x
#else
#define debug_print(x) ;
#endif

#define WG_SUCCESS 0
#define WG_FAIL    1

#define WG_DEFAULT_SIZE 20

typedef struct node_t
{
    int            vertex;
    int            num_edges;
    int            weight;
    void *         data;
    struct node_t *next;
} node_t;

typedef node_t *(*SEARCH_F)(void *, int, int);

typedef void (*FREE_F)(void *);

typedef void (*BFS_F)(void *, int, int);

typedef struct graph_t
{
    int      num_verts;
    node_t **adj_lists;
    SEARCH_F search_func;
    FREE_F   custom_free;
    BFS_F    bfs_algorithm;
} graph_t;

node_t *wg_new_node(int vertex, int weight, void *data);

graph_t *wg_create(int vertices, SEARCH_F, FREE_F, BFS_F);

int wg_remove(graph_t *graph, int src, int dst);

void wg_print(graph_t *graph);

int wg_destroy(graph_t *graph);

int wg_add_edge(graph_t *graph,
                int      src,
                int      dst,
                int      weight,
                void *   src_data,
                void *   dst_data);

node_t *wg_search_edge(void *graph, int src, int dst);

void free_func(void *arg);

void bfs_calc(void *graph, int start_vertex, int num_verts);

#endif
