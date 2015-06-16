#ifndef __PAA_TRAB2_H__
#define __PAA_TRAB2_H__

#include <string.h>
#include <float.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef double (*penalidade_fn)(char, char);
typedef struct _solucao_t  solucao_t;

solucao_t *
solucao_new(size_t,size_t, solucao_t*);

void
solucao_print(solucao_t *);

void
solucao_destroy(solucao_t**);


double 
alinhamento_quadratico_custo(const char *origem, const size_t m, const char*destino, const size_t n, const double gap, const penalidade_fn penalidade);

double 
alinhamento_quadratico_custo_matriz(const char *origem, const size_t m, const char*destino, const size_t n, const double gap, const penalidade_fn penalidade,
				    double M[m+1][n+1]);

solucao_t *
procurar_solucao_quadratico(const char *origem, const size_t m, const char*destino, const size_t n, const double gap, const penalidade_fn penalidade);




double
alinhamento_linear_custo(char *origem, size_t m, char*destino,size_t n, double gap, penalidade_fn penalidade);


#endif
