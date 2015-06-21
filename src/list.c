#include "trab2.h"


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
    list->cursor=i;
    list->sz++;
    
    return 0;
}

int
list_push(list_t *list,  void *item){
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

    list->cursor=i;

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
    list->cursor=list->first;
    
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
list_size(const list_t *list) {
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

bool
list_exists(list_t *list, const void *data){
    assert (list);
    assert (data);
    item_t *cursor = list->first;
    while(cursor) {
	if(cursor->data == data)
	    return true;
	cursor = cursor -> next;
    }
    return false;
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
_cmp(const void* k1, const void* k2){
    return strcmp((char *) k1, (char *) k2);
}


void *
list_item (list_t *list) {
    assert (list);
    
    if(!list->cursor)
	return NULL;

    return list->cursor->data;
}
    

int
list_insert(list_t *list, void *ref, void *data){
    assert(list);
    assert(ref);
    assert(data);
    
    list->cursor = list->first;
    while(list->cursor) {
	if(list->cursor->data == ref)
	    break;
	list->cursor = 	list->cursor->next;
    }

    /* 
       se cursor é NULL,e então ref não foi localizado, 
       retorna erro...
     */
    if (!list->cursor)
	return -1;
    
    item_t *next = list->cursor->next;

    item_t *new= s_item_new(data);

    if (!new)
	return -1;

    new->next = next;
    new->prev = list->cursor;
    list->cursor->next = new;

    if(next)
	next->prev = new;

    list->sz++;
    return 0;
	
}

void *
list_remove(list_t *list, void *ref){
    assert(list);
    assert(ref);
    
    list->cursor = list->first;
    while(list->cursor) {
	if(list->cursor->data == ref)
	    break;
	list->cursor = 	list->cursor->next;
    }


    /* 
       se cursor é NULL,e então ref não foi localizado, 
       retorna erro...
     */
    if (!list->cursor)
	return NULL;

    item_t *prev = list->cursor->prev;

    item_t *next=  list->cursor->next;;

    if (list->last == list->cursor)
	list->last= prev;
    if (list->first == list->cursor)
	list->first= next;


    if (prev)
	prev->next = next;

    if(next)
	next->prev = prev;

    void *data = list->cursor->data;
    
    s_item_destroy (&list->cursor);
    list->cursor=list->first;
    list->sz--;

    return data;
	
}
    
 

void *
list_find(list_t *list, void *ref, cmp_fn *cmp_fn){
    assert(list);
    assert(ref);

    if(!cmp_fn)
	cmp_fn=_cmp;

    list->cursor = list->first;
    while(list->cursor) {
	if(0==cmp_fn(list->cursor->data, ref))
	    break;
	list->cursor = 	list->cursor->next;
    }
    
    return list->cursor?list->cursor->data:NULL;
};

/*
static int
s_compare (void *item1, void *item2)
{
    return strcmp ((char *) item1, (char *) item2);
}
*/

void
list_selftest(void){

    printf("list selftest...");

    //  @selftest
    list_t *list = list_new ();
    assert (list);
    assert (list_size (list) == 0);

    //  Three items we'll use as test data

    char *cheese = "boursin";
    char *bread = "baguette";
    char *wine = "bordeaux";

    list_append (list, cheese);
    assert (list_size (list) == 1);
    assert ( list_exists (list, cheese));
    assert (!list_exists (list, bread));
    assert (!list_exists (list, wine));
    list_append (list, bread);
    assert (list_size (list) == 2);
    assert ( list_exists (list, cheese));
    assert ( list_exists (list, bread));
    assert (!list_exists (list, wine));
    list_append (list, wine);
    assert (list_size (list) == 3);
    assert ( list_exists (list, cheese));
    assert ( list_exists (list, bread));
    assert ( list_exists (list, wine));

    assert (list_first (list) == cheese);

    assert (list_first (list) == cheese);
    assert (list_last (list) == wine);
    assert (list_next (list) == NULL);

    assert (list_first (list) == cheese);
    assert (list_next (list) == bread);
    assert (list_next (list) == wine);
    assert (list_next (list) == NULL);

    assert (list_size (list) == 3);

    list_remove (list, wine);
    assert (list_size (list) == 2);

    assert (list_first (list) == cheese);
    list_remove (list, cheese);
    assert (list_size (list) == 1);
    assert (list_first (list) == bread);

    list_remove (list, bread);
    assert (list_size (list) == 0);

    list_append (list, cheese);
    list_append (list, bread);
    assert (list_last (list) == bread);
    list_remove (list, bread);
    assert (list_last (list) == cheese);
    list_remove (list, cheese);
    assert (list_last (list) == NULL);

    list_push (list, cheese);
    assert (list_size (list) == 1);
    assert (list_first (list) == cheese);

    list_push (list, bread);
    assert (list_size (list) == 2);
    assert (list_first (list) == bread);
    assert (list_item (list) == bread);

    list_append (list, wine);
    assert (list_size (list) == 3);
    assert (list_first (list) == bread);

    /*
    list_sort (list, s_compare);

    char *item;
    item = (char *) list_pop (list);
    assert (item == bread);
    item = (char *) list_pop (list);
    assert (item == wine);
    item = (char *) list_pop (list);
    assert (item == cheese);
    assert (list_size (list) == 0);

    */

    list_destroy (&list);

    printf("ok\n");
}
