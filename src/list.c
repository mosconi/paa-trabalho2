#include "list.h"

typedef struct _item_t {
    void *data;
    struct _item_t *next;
    struct _item_t *prev;
} item_t;

struct _list_t {
    item_t *first;
    item_t *last;
    item_t *curr;
    
};

list_t *
list_new(void);

void
list_destroy(list_t **list_p);

int
list_append(list_t *list, void *item);

int
list_push(list_t *list, void *item);

void *
list_pop(list_t *list);

void *
list_tail(list_t *list);

size_t
list_size(list_t *list);

void *
list_first(list_t *list);

void *
list_last(list_t *list);

void *
list_next(list_t *list);

void *
list_prev(list_t *list);

void *
list_find(list_t *list, const void *data, cmp_fn *cmp_fn);

