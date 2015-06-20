#include "list.h"


typedef struct _item_t {
    void *data;
    struct _item_t *next;
    struct _item_t *prev;
} item_t;

static item_t *
s_item_new(void *data){
    item_t *self = calloc(sizeof(item_t),1);
    if (!self) return NULL;

    self->data = data;
    self->next = NULL;
    self->prev = NULL;
    
    return self;
	
}

static void
s_item_destroy (item_t **item_p){
    assert(item_p);
    if (!*item_p) return;
    item_t *item = *item_p;

    if (item->prev)
	item->prev->next=NULL;
    if (item->next)
	item->next->prev=NULL;
    
    free (item);
    *item_p = NULL;
}

struct _list_t {
    item_t *first;
    item_t *last;
    item_t *cursor;
    size_t sz;
};

list_t *
list_new(void){
    list_t *self = calloc(sizeof(list_t),1);
    if (!self) return NULL;
    self->first =NULL;
    self->last =NULL;
    self->cursor =NULL;
    self->sz=0;

    return self;
}

void
list_destroy(list_t **list_p){
    assert(list_p);
    if(!*list_p) return;
    list_t *list = *list_p;

    free(list);
    
    *list_p=NULL;
}

int
list_append(list_t *list, void *item){
    assert(list);
    assert(item);

    item_t *i = s_item_new(item);

    if (!i) return -1;

    i->prev = list->last;
    if(!list->first)
	list->first = i;
    if(list->last)
	list->last->next = i;
    list->last=i;

    list->sz++;
    
    return 0;
}

int
list_push(list_t *list, void *item){
    assert(list);
    assert(item);

    item_t *i = s_item_new(item);

    if (!i) return -1;

    i->next = list->first;
    if(!list->last)
	list->last = i;
    if(list->first)
	list->first->prev = i;
    list->first=i;

    list->sz++;
    
    return 0;
}


void *
list_pop(list_t *list){
    assert(list);

    item_t *i = list->first;

    if(!i) return NULL;

    list->first = i->next;
    if(list->first)
	list->first->prev=NULL;
    
    if(list->last == i )
	list->last=NULL;

    
    void *data=i->data;

    s_item_destroy(&i);

    list->sz--;
    return data;
}

void *
list_tail(list_t *list){
        assert(list);

    item_t *i = list->last;

    list->last = i->prev;
    list->last->next=NULL;
    
    void *data=i->data;

    s_item_destroy(&i);

    list->sz--;

    return data;
}

size_t
list_size(list_t *list) {
    assert(list);
    return list->sz;
}

void *
list_first(list_t *list){
    assert (list);
    list->cursor = list->first;
    return list->cursor?list->cursor->data:NULL;
}

void *
list_last(list_t *list){
    assert (list);
    list->cursor = list->last;
    return list->cursor?list->cursor->data:NULL;
}


void *
list_next(list_t *list){
    assert (list);

    if(!list->cursor)
	return NULL;

    list->cursor = list->cursor->next;
    return list->cursor?list->cursor->data:NULL;
}


void *
list_prev(list_t *list){
    assert (list);

    if(!list->cursor)
	return NULL;

    list->cursor = list->cursor->prev;
    return list->cursor?list->cursor->data:NULL;
}

static int
_cmp(const void* k1,const void* k2){
    return strcmp((char *) k1, (char *) k2);
}


void *
list_find(list_t *list, const void *data, cmp_fn *cmp_fn){
    assert(list);
    assert(data);

    if(!cmp_fn)
	cmp_fn=_cmp;

    list->cursor = list->first;
    while(list->cursor) {
	if(0==cmp_fn(list->cursor->data, data))
	    break;
	list->cursor = 	list->cursor->next;
    }
    
    return list->cursor?list->cursor->data:NULL;
};

void
list_selftest(void){

    printf("list selftest...");
    
    list_t * list = list_new();
    assert(list);

    list_destroy(&list);
    assert(NULL==list);

    list = list_new();

    assert(0==list_size(list));

    char *val = strdup("item 01");
    list_append(list, val);
    assert(1==list_size(list));

    assert(0==strcmp(list_first(list),"item 01"));
    assert(strcmp(list_first(list),"item 02"));

    char *p =NULL;

    while (NULL!=(p=list_pop(list)))
	free(p);
    
    
    list_destroy(&list);
    printf("ok\n");
}
