#include "trab2.h"

struct _solucao_t {
    size_t pos_A;
    size_t pos_B;
    struct _solucao_t *proximo;
};

static double
s_min(double list[]){
    double *p=list;
    
    double min= *p;
    
    while (!isnan(*p)){
	if ((min > *p) )
	    min = *p;
	p++;
    }
    return min;
}

#define min(...) s_min((double []){__VA_ARGS__,NAN})


double 
alinhamento_quadratico_custo(const char *origem, const size_t m, const char* destino, const size_t n, const double gap, penalidade_fn penalidade){

    double M[m+1][n+1];

    double val = alinhamento_quadratico_custo_matriz(origem, m,  destino, n, gap, penalidade,M);

    return val;
}

double 
alinhamento_quadratico_custo_matriz(const char *origem, const size_t m, const char* destino, const size_t n, const double gap, penalidade_fn penalidade,
				    double M[m+1][n+1]){

    
    for (int i=0; i<=m;i++){
	M[i][0]= i*gap;
    }
    for (int j=0; j<=n;j++){
	M[0][j]= j*gap;
    }

    for (int i=1; i<=m; i++) {
	for (int j=1; j<=n;j++){
	    double val1=penalidade(origem[i-1],destino[j-1]) + M[i-1][j-1];
	    double val2=gap + M[i-1][j];
	    double val3=gap + M[i][j-1];

	    M[i][j] = min(val1,val2,val3);
	}
    }
    return M[m][n];
}


double
alinhamento_linear_custo(const char *origem, size_t m, const char*destino, size_t n, double gap, penalidade_fn penalidade){
    double corrente[m];
    double ultimo[m];

    for (int i=0; i<=m; i++)
	corrente[i] = i*gap;


    for (int j=1; j<=n;j++) {	
	for (int i=0; i<=m; i++)
	    ultimo[i] = corrente[i];
	
	corrente[0] = j*gap;

	for (int i=1; i<=m; i++){
	    double val1=
		penalidade(origem[i-1],destino[j-1])
		+ ultimo[i-1];
	    double val2=gap + corrente[i-1];
	    double val3=gap + ultimo[i];

	    corrente[i] = min (val1, val2, val3);
	}
    }
    
    
    return corrente[m];
}


solucao_t *
procurar_solucao_quadratico(const char *origem, const size_t m, const char*destino, const size_t n, const double gap, penalidade_fn penalidade){
    double M[m+1][n+1];

    alinhamento_quadratico_custo_matriz(origem, m,  destino, n, gap, penalidade,M);

    size_t i= m;  size_t j= n;

    solucao_t *solucao=NULL;

    while (i && j) {
	if (M[i][j] == penalidade(origem[i-1],destino[j-1]) + M[i-1][j-1]) {
	    solucao = solucao_new(--i,--j,solucao);
	} else if (M[i][j] == gap + M[i-1][j]) {
	    i--;
	} else if (M[i][j] == gap + M[i][j-1]) {
	    j--;
	} else {
	    /*  Erro!!!! */
	    solucao_destroy(&solucao);
	    return NULL;
	}
    }
    return solucao;

}

solucao_t *
solucao_new(size_t i, size_t j, solucao_t *sol) {
    solucao_t *self = calloc (sizeof(struct _solucao_t),1);
    if (!self) return NULL;
    
    self->pos_A=i; self->pos_B=j;
    self->proximo = sol;

    return self;
};

void
solucao_destroy (solucao_t **self_p) {
    if (!*self_p) return;
    solucao_t *self = *self_p;
    while (self) {
	solucao_t *p = self->proximo;
	free(self);
	self=p;
    }
    *self_p=NULL;
}

void
solucao_print(solucao_t *self) {
    solucao_t *p=self;
    while (p) {
	printf("(%zu,%zu) ",p->pos_A, p->pos_B);
	p=p->proximo;
    }
    
    printf("\n");
}

solucao_t *
procurar_solucao_linear(const char *origem, const size_t m, const char*destino, const size_t n, const double gap, penalidade_fn penalidade){

    return NULL;
}
