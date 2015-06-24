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
#include <signal.h>

#if (defined (_MSC_VER))
#   if (!defined (__cplusplus) && (!defined (true)))
#       define true 1
#       define false 0
        typedef char bool;
#   endif
#else
#   include <stdbool.h>
#endif

#if defined(_WIN32)
#include <windows.h>
#include <psapi.h>

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
#include <unistd.h>
#include <sys/resource.h>

#if defined(__APPLE__) && defined(__MACH__)
#include <mach/mach.h>

#elif (defined(_AIX) || defined(__TOS__AIX__)) || (defined(__sun__) || defined(__sun) || defined(sun) && (defined(__SVR4) || defined(__svr4__)))
#include <fcntl.h>
#include <procfs.h>

#elif defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
#include <stdio.h>

#endif

#else
#error "Cannot define getPeakRSS( ) or getCurrentRSS( ) for an unknown OS."
#endif

#include "rss.h"


#define streq(A,B) 0==strcmp(A,B)

extern bool print_memory_usage;

typedef double (*penalidade_fn)(char, char);
typedef struct _solucao_t  solucao_t;

solucao_t *
solucao_new(size_t,size_t, solucao_t*);

void
solucao_print(solucao_t *);

void
solucao_destroy(solucao_t**);

bool
solucao_eq(solucao_t*, solucao_t*);

solucao_t *
solucao_merge(solucao_t*, solucao_t*);

double 
opt_quadratico(const char *origem, const size_t m, const char*destino, const size_t n, const double gap, penalidade_fn penalidade);

double 
opt_quadratico_matriz(const char *origem, const size_t m,
		      const char*destino, const size_t n,
		      const double gap, penalidade_fn penalidade,
		      double **M);

double
find_sol_quadratico(const char *origem, const size_t m, const char*destino, const size_t n, const double gap, penalidade_fn penalidade, solucao_t **);

double 
find_sol_linear(const char *origem, const size_t m, const char*destino, const size_t n, const double gap, penalidade_fn penalidade, solucao_t **);


double
opt_linear(const char *origem, const size_t m, const char*destino, const size_t n, const double gap, penalidade_fn penalidade);

double
opt_linear2(const char *origem, const size_t m, const char*destino, const size_t n, const double gap, penalidade_fn penalidade);


double
opt_linear_array(const char *origem, const size_t m, const char*destino, const size_t n, const double gap, penalidade_fn penalidade,double array[m+1]);

typedef double
(*opt_fn)(const char *origem, const size_t m,
	  const char*destino, const size_t n,
	  const double gap, penalidade_fn penalidade,
	  solucao_t **) ;

#endif
