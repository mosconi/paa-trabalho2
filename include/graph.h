#ifndef __GRAPH_H__
#define __GRAPH_H__

typedef struct _adjlist_t adjlist_t;

typedef struct _graph_t graph_t;

typedef void (data_destroy_fn)(void **data) ;
typedef int (data_cmp_fn)(const void *key1,const void *key2) ;
typedef void* (data_copy_fn)(const void *data) ;

graph_t *
graph_new( data_cmp_fn * data_cmp_fn, data_destroy_fn* data_destroy_fn, data_copy_fn *data_copy_fn);

void
graph_destroy(graph_t **);

int
graph_add_vertex(graph_t *graph, const void *data);

int
graph_add_edge(graph_t *graph, const void *data1, const void *data2 );

int
graph_del_vertex(graph_t *graph, const void *data);

int
graph_del_edge(graph_t *graph, const void *data1, const void *data2);

adjlist_t *
graph_adjlist(graph_t *graph, const void *data);

int
graph_is_adjacent(graph_t *graph, const void *key1, const void *key2 );

size_t
graph_vcount(graph_t *graph);

size_t
graph_ecount(graph_t *graph);

void
graph_selftest(void);

#endif
