#ifndef __LIST_H__
#define __LIST_H__

#define _DEFAULT_SOURCE
#define _GNU_SOURCE

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef int (cmp_fn)(const void *k1,const void *k2);

typedef struct _list_t list_t;

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

void
list_selftest (void);

#endif
