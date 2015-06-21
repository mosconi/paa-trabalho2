#include "trab2.h"

struct _set_t {
    list_t *list;
    set_destroy_fn destroy;
    set_cmp_fn cmp;
};

set_t *
set_new (set_cmp_fn cmp, set_destroy_fn destroy){
    set_t * self=calloc(sizeof(set_t),1);

    if (!self)
	return NULL;
    
    self->list=list_new();
    self->destroy= destroy;
    self->cmp = cmp;
    
    if (!self->list){
	free(self);
	self = NULL;
    }
	
    return self;
}

void
set_destroy (set_t **set_p){
    assert (set_p);
    if (!*set_p) return;

    set_t *set = *set_p;
    void *p = NULL;
    while ((p = list_pop(set->list))) 
	set->destroy(&p);
    
    list_destroy(&set->list);
    free(set);

    *set_p = NULL;
    
}

int
set_insert (set_t *set, void *data){
    assert(set);

    if(list_find(set->list, data, set->cmp))
	return 0;

    return list_append(set->list, data);
}

void *
set_remove (set_t *set, void *data){
    assert(set);
    assert (data);
    return list_remove(set->list, data);
}

set_t *
set_union(set_t *set1, set_t *set2){
    assert(set1);
    assert(set2);

    set_t *setu= set_new(set1->cmp,set1->destroy);
    
    return setu;
}

set_t *
set_union_n(set_t *sets[]);

#define set_vaunion(...) set_union_n({__VA_ARGS__,NULL})

set_t *
set_intersection(set_t *set1, set_t *set2);

set_t *
set_difference(set_t *set1, set_t *set2);

size_t
set_size(const set_t *set){
    assert (set);
    return list_size(set->list);
}

bool
set_hasmember (const set_t *set, void *data){
    assert (set);
    assert (data);

    if (list_find(set->list, data, set->cmp))
	return true;

    return false;	    
}

bool
set_subset (const set_t *set1, const set_t * set2){
    assert (set1);
    assert (set2);

    if (set_size(set1) > set_size(set2))
	return false;

    
    for  (void *data = list_first(set1->list); 
	  data;
	  data = list_next(set1->list)) {
	if (set_hasmember(set2, data)){
	    return true;
	}
    }
    
    return false;
}


int
set_cmp (const set_t *set1, const set_t *set2){
    assert (set1);
    assert (set2);
    
    if (set_size(set1) > set_size(set2))
	return 1;
    if (set_size(set1) < set_size(set2))
	return -1;

    void *data1;
    void *data2;
    
    for (data1 = list_first(set1->list); 
	  data1;
	  data1 = list_next(set1->list)) {
	if (set_hasmember(set2, data1))
	    break;
    }

    for (data2 = list_first(set2->list); 
	  data2;
	  data2 = list_next(set2->list)) {
	if (set_hasmember(set1, data2))
	    break;
    }

    
    return (set1->cmp)(data1, data2);
}

void
set_selftest(void){
    

}
