#ifndef __PAA_TRAB2_H__
#define __PAA_TRAB2_H__

#include <string.h>
#include <float.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>

typedef double (*penalidade_fn)(char, char);

double
alinhamento_quadratico_custo(char *origem, size_t m, char*destino,size_t n, double gap, penalidade_fn penalidade);


double
alinhamento_linear_custo(char *origem, size_t m, char*destino,size_t n, double gap, penalidade_fn penalidade);


#endif
