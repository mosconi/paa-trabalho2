#ifndef __PAA_TRAB2_H__
#define __PAA_TRAB2_H__

//#define _DEFAULT_SOURCE
#define _GNU_SOURCE

#include <assert.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <stddef.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
/* for ETIMEDOUT */
#include <errno.h>

#if (defined (_MSC_VER))
#   if (!defined (__cplusplus) && (!defined (true)))
#       define true 1
#       define false 0
        typedef char bool;
#   endif
#else
#   include <stdbool.h>
#endif

#include "list.h"
#include "set.h"
#include "graph.h"

#define streq(A,B) 0==strcmp(A,B)

typedef double (*penalidade_fn)(char, char);
typedef struct _solucao_t  solucao_t;

solucao_t *
solucao_new(size_t,size_t, solucao_t*);

void
solucao_print(solucao_t *);

void
solucao_destroy(solucao_t**);


double 
alinhamento_quadratico_custo(const char *origem, const size_t m, const char*destino, const size_t n, const double gap, penalidade_fn penalidade);

double 
alinhamento_quadratico_custo_matriz(const char *origem, const size_t m, const char*destino, const size_t n, const double gap, penalidade_fn penalidade,
				    double M[m+1][n+1]);

solucao_t *
procurar_solucao_quadratico(const char *origem, const size_t m, const char*destino, const size_t n, const double gap, penalidade_fn penalidade);

solucao_t *
procurar_solucao_linear(const char *origem, const size_t m, const char*destino, const size_t n, const double gap, penalidade_fn penalidade);


double
alinhamento_linear_custo(const char *origem, const size_t m, const char*destino, const size_t n, const double gap, penalidade_fn penalidade);

typedef solucao_t *
(*alinhamento_fn)(const char *origem, const size_t m, const char*destino, const size_t n, const double gap, penalidade_fn penalidade) ;

#endif
