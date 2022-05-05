/**
 * @file   weighted_graph.c
 * @author Jon S Hall
 * @brief  weighted graph
 * @date   December 2021
 */

#include <weighted_graph.h>

/**
 * @references:
 * https://www.programiz.com/dsa/graph-adjacency-list
 */

node_t *
wg_new_node(int vertex, int weight, void *data)
{
    node_t *node = { 0 };

    if (NULL == (node = calloc(1, sizeof(node_t))))
    {
        fprintf(stderr, "ERROR: Calloc failed to create node\n");
        goto FAIL;
    }

    node->data   = data;
    node->vertex = vertex;
    node->weight = weight;
    node->next   = NULL;

    debug_print(("--------------------------------------------\n"));
    debug_print(("wg_new_node: node created\n"));
    debug_print(("--------------------------------------------\n"));

    goto EXIT;

FAIL:
    node = NULL;

EXIT:
    return (node);
}

graph_t *
wg_create(int      vertices,
          SEARCH_F search_func,
          FREE_F   custom_free,
          BFS_F    bfs_algorithm)
{
    int inc = 0;

    graph_t *graph = { 0 };

    if (0 > vertices)
    {
        fprintf(stderr, "ERROR: invalid number passed to create wg\n");
        goto FAIL;
    }

    // calloc graph
    if (NULL == (graph = calloc(1, sizeof(graph_t))))
    {
        fprintf(stderr, "ERROR: Calloc failed to create graph\n");
        goto FAIL;
    }

    // calloc adj lists
    if (NULL == (graph->adj_lists = calloc(vertices, sizeof(node_t *))))
    {
        fprintf(stderr, "ERROR: Calloc failed create graph\n");
        goto FAIL;
    }

    // assign num verticies
    graph->num_verts     = vertices;
    graph->search_func   = search_func;
    graph->custom_free   = custom_free;
    graph->bfs_algorithm = bfs_algorithm;

    debug_print(("--------------------------------------------\n"));
    debug_print(("wg_create: graph created\n"));
    debug_print(("--------------------------------------------\n"));

    goto EXIT;

FAIL:
    free_func(graph);
    graph = NULL;

EXIT:
    return (graph);
}

int
wg_remove(graph_t *graph, int src, int dst)
{
    int status = WG_SUCCESS;

    node_t *remove_src = { 0 };
    node_t *remove_dst = { 0 };
    node_t *temp_src   = { 0 };
    node_t *temp_dst   = { 0 };

    debug_print(("--------------------------------------------\n"));

    temp_src = graph->adj_lists[src];

    while (NULL != temp_src)
    {
        if (NULL != temp_src->next)
        {
            if (dst == temp_src->next->vertex)
            {
                printf("remove: found edge between: %d and %d\n",
                       src,
                       temp_src->next->vertex);
                remove_src     = temp_src->next;
                temp_src->next = remove_src->next;
                break;
            }
        }

        temp_src = temp_src->next;
    }

    temp_dst = graph->adj_lists[dst];

    while (NULL != temp_dst)
    {
        if (NULL != temp_dst->next)
        {
            if (src == temp_dst->next->vertex)
            {
                printf("remove: found edge between: %d and %d\n",
                       dst,
                       temp_dst->next->vertex);
                remove_dst     = temp_dst->next;
                temp_dst->next = remove_dst->next;
                break;
            }
        }
    }

    // check, free and null
    if (NULL != remove_src)
    {
        remove_src->data = NULL;
        free_func(remove_src);
    }

    if (NULL != remove_dst)
    {
        remove_dst->data = NULL;
        free_func(remove_dst);
    }

    goto END;

FAIL:
    status = WG_FAIL;

END:
    return status;
}

void
wg_print(graph_t *graph)
{
    int vertex = 0;

    node_t *temp = { 0 };

    debug_print(("--------------------------------------------\n"));

    for (vertex = 0; vertex < graph->num_verts; vertex++)
    {
        temp = graph->adj_lists[vertex];

        printf("\n vertex %d:\n ", vertex);
        printf(" temp   %p:\n ", temp);

        while (NULL != temp)
        {
            printf("%d (%s) -> ", temp->vertex, (char *)temp->data);
            temp = temp->next;
        }
    }

    debug_print(("--------------------------------------------\n"));
}

int
wg_destroy(graph_t *graph)
{
    int status = WG_SUCCESS;
    int inc    = 0;

    debug_print(("--------------------------------------------\n"));

    // check input
    if (NULL == graph)
    {
        debug_print(("wg is NULL\n"));
        goto END;
    }

    node_t *clear = NULL;
    node_t *temp  = { 0 };

    for (inc = 0; inc < graph->num_verts; inc++)
    {
        clear = graph->adj_lists[inc];
        while (NULL != clear)
        {
            temp  = clear;
            clear = clear->next;
            free_func(temp);
        }
    }

    free_func(graph->adj_lists);
    free_func(graph);

    goto END;

FAIL:
    status = WG_FAIL;

END:
    return (status);
}

int
wg_add_edge(graph_t *graph,
            int      src,
            int      dst,
            int      weight,
            void *   src_data,
            void *   dst_data)
{
    int status = WG_SUCCESS;

    // add edge from src to dst
    node_t *dst_node = { 0 };
    node_t *src_node = { 0 };

    if (NULL == (dst_node = wg_new_node(dst, weight, dst_data)))
    {
        fprintf(stderr, "ERROR: Null dst node\n");
        goto FAIL;
    }

    if (NULL == (src_node = wg_new_node(src, weight, src_data)))
    {
        fprintf(stderr, "ERROR: Null src nodes\n");
        goto FAIL;
    }

    // add edge from src to dst
    src_node->next        = graph->adj_lists[dst];
    graph->adj_lists[dst] = src_node;
    src_node->num_edges++;

    debug_print(("--------------------------------------------\n"));
    debug_print(("wg_add_edge: src edge added: %d\n", src));
    debug_print(("--------------------------------------------\n"));

    // add edge from dst to src
    dst_node->next        = graph->adj_lists[src];
    graph->adj_lists[src] = dst_node;
    dst_node->num_edges++;

    debug_print(("--------------------------------------------\n"));
    debug_print(("wg_add_edge: dst edge added %d\n", dst));
    debug_print(("--------------------------------------------\n"));

    goto EXIT;

FAIL:
    free_func(dst_node);
    free_func(src_node);
    status = WG_FAIL;

EXIT:
    return (status);
}

node_t *
wg_search_edge(void *graph, int src, int dst)
{
    node_t * temp         = { 0 };
    graph_t *search_graph = { 0 };

    search_graph = (graph_t *)graph;
    temp         = search_graph->adj_lists[src];

    debug_print(("--------------------------------------------\n"));

    while (NULL != temp)
    {
        if (dst == temp->vertex)
        {
            printf("search_edge: found edge between: %d and %d\n",
                   src,
                   temp->vertex);
            goto END;
        }

        temp = temp->next;
    }

    temp = NULL;

END:
    return temp;
}

void
free_func(void *arg)
{
    if (NULL != arg)
    {
        free(arg);
        arg = NULL;
    }
}

void
bfs_calc(void *graph, int start_vertex, int num_verts)
{
    bool visited[num_verts];
    int  inc            = 0;
    int  current_vertex = 0;
    int  adj_vertex     = 0;
    int  src_vertex     = 0;
    int  distance       = 0;

    queue_t *     queue     = NULL;
    graph_t *     bfs_graph = NULL;
    queue_node_t *deq_node  = NULL;
    node_t *      temp      = NULL;

    bfs_graph = (graph_t *)graph;

    debug_print(("--------------------------------------------\n"));

    if (NULL == (queue = queue_init()))
    {
        fprintf(stderr, "bfs_calc: queue is NULL\n");
        goto FAIL;
    }

    for (inc = 0; inc < bfs_graph->num_verts; inc++)
    {
        visited[inc] = false;
    }

    visited[start_vertex] = true;

    queue_enqueue(queue, &start_vertex);

    while (1 == queue_emptycheck(queue))
    {
        queue_traverse(queue);

        debug_print(("--------------------------------------------\n"));

        if (NULL == (deq_node = queue_dequeue(queue)))
        {
            fprintf(stderr, "bfs_calc: dequeue node is NULL\n");
            goto FAIL;
        }

        current_vertex = *(int *)deq_node->data;

        free(deq_node);

        printf("bfs_calc: visited Node: %d\n", current_vertex);

        temp = bfs_graph->adj_lists[current_vertex];

        while (NULL != temp)
        {
            if (false == visited[temp->vertex])
            {
                printf("bfs_calc: weight:           %d\n", temp->weight);
                printf("bfs_calc: current distance: %d\n",
                       distance += temp->weight);
                visited[temp->vertex] = true;
                queue_enqueue(queue, &temp->vertex);
            }

            temp = temp->next;
        }
    }

    debug_print(("--------------------------------------------\n"));
    printf("bfs_calc: distance:     %d\n", distance);
    debug_print(("--------------------------------------------\n"));

FAIL:
    queue_destroy(&queue);
}

void
int_free(void *arg)
{
    free((int *)arg);
}
