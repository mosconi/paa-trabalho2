#include "graph.h"

struct _graph_t {
    size_t vcount;
    size_t ecount;

    data_copy_fn *copy_fn;
    data_cmp_fn *cmp_fn;
    data_destroy_fn *destroy_fn;
   
};


static void
_destroy(void **str_p){
    assert(str_p);
    if (!str_p) return;
    free(*str_p);
    *str_p=NULL;
}

static void *
_copy(const void *str){
    return strdup((char *) str);
}

 int
_cmp(const void *k1, const void *k2){
    return strcmp((char *) k1, (char *)k2);
}


graph_t *
graph_new( data_cmp_fn * data_cmp_fn, data_destroy_fn* data_destroy_fn, data_copy_fn *data_copy_fn){

    graph_t *self = calloc(sizeof(graph_t),1);

    self->vcount = 0 ;
    self->ecount = 0 ;

    self->copy_fn = _copy;
    self->cmp_fn = _cmp;
    self->destroy_fn = _destroy;
    
    if(data_copy_fn) 
	self->copy_fn = data_copy_fn;
    
    if(data_cmp_fn) 
	self->cmp_fn = data_cmp_fn;

    if(data_destroy_fn) 
	self->destroy_fn = data_destroy_fn;

    
    return self;
}


void
graph_destroy(graph_t **self_p){
    assert(self_p);

    if(!*self_p) return ;

    graph_t *self = *self_p;

    free (self);

    *self_p = NULL;

}


int
graph_add_vertex(graph_t *graph, const void *data){
    assert(graph);
    assert(data);

    return 0;
}


int
graph_add_edge(graph_t *graph, const void *data1, const void *data2 ){
    assert(graph);
    assert(data1);
    assert(data2);

    return 0;

}


int
graph_del_vertex(graph_t *graph, const void *data){
    assert(graph);
    assert(data);

    return 0;

}


int
graph_del_edge(graph_t *graph, const void *data1, const void *data2){
    assert(graph);
    assert(data1);
    assert(data2);

    return 0;
}


adjlist_t *
graph_adjlist(graph_t *graph, const void *data){
    assert(graph);
    assert(data);

    return 0;
}


int
graph_is_adjacent(graph_t *graph, const void *key1, const void *key2 ){
    assert(graph);
    assert(key1);
    assert(key2);

    return 0;

}


size_t
graph_vcount(graph_t *graph){
    assert(graph);
    
    return graph->vcount;
}


size_t
graph_ecount(graph_t *graph){
    assert(graph);
    
    return graph->ecount;
}


