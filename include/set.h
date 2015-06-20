#ifndef __SET_H__
#define __SET_H__

typedef struct _set_t set_t;

typedef int (*set_cmp_fn)(const void*, const void* );
typedef void (*set_destroy_fn)(void **);

set_t *
set_new (set_cmp_fn , set_destroy_fn );

void
set_destroy (set_t **);

int
set_insert (set_t *, const void *data);

int
set_remove (set_t *, const void *data);

set_t *
set_union(set_t *set1, set_t set2);

set_t *
set_union_n(set_t *sets[]);

#define set_vaunion(...) set_union_n({__VA_ARGS__,NULL})

set_t *
set_intersection(set_t *set1, set_t set2);

set_t *
set_difference(set_t *set1, set_t set2);

size_t
set_size(const set_t *);

bool
set_hasmenber (const set_t *set, const void *data);

bool
set_subset (const set_t *set, const set_t * set2);

int
set_cmp (const set_t *set, const set_t *set2);

void
set_selftest (void);

#endif
