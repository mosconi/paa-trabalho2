#include "trab2.h"

/*
  TODO:

  - Trocar nomes alinhamento_()_custo para OPT_()
  - Trocar nomes proc..._()_custo para find_sol_()

*/

bool print_memory_usage=false;

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
alinhamento_quadratico_custo_matriz(const char *origem, const size_t m,
				    const char* destino, const size_t n,
				    const double gap, penalidade_fn penalidade,
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
    double corrente[m+1];

    alinhamento_linear_custo_array(origem,m,destino,n,gap,penalidade,corrente);
    
    return corrente[m];
}

double
alinhamento_linear_custo_array(const char *origem, size_t m, const char*destino, size_t n, double gap, penalidade_fn penalidade,double array[m+1]){
    double corrente[m+1];
    double ultimo[m+1];

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
    
    for (int i = 0; i<=m; i++)
	array[i] = corrente[i];
    
    return corrente[m];
}




solucao_t *
procurar_solucao_quadratico(const char *origem, const size_t m, const char*destino, const size_t n, const double gap, penalidade_fn penalidade){
    double M[m+1][n+1];

    double val = alinhamento_quadratico_custo_matriz(origem, m,  destino, n, gap, penalidade,M);
    /*
    fprintf(stderr, "      minval : %f\n", val); 
    */
    if (val) {}
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
    if(print_memory_usage)
	printf("    memoria (current): %zu\n", getCurrentRSS() );
    
    return solucao;

}

static solucao_t *
procurar_solucao_base(const char *origem, const size_t m,
		      const char*destino, const size_t n,
		      const double gap, penalidade_fn penalidade,
		      size_t base_m,size_t base_n ){
    double M[m+1][n+1];

    alinhamento_quadratico_custo_matriz(origem, m,  destino, n, gap, penalidade,M);

    size_t i= m;  size_t j= n;

    solucao_t *solucao=NULL;

    while (i && j) {
	if (M[i][j] == penalidade(origem[i-1],destino[j-1]) + M[i-1][j-1]) {
	    solucao = solucao_new(--i+base_m,--j+base_n,solucao);
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
solucao_merge(solucao_t *s1,solucao_t *s2) {
    solucao_t *p=s1;

    if (!p) return s2;
    while (p->proximo)	p=p->proximo;

    p->proximo = s2;
    
    return s1;
}

bool
solucao_eq(solucao_t *s1,solucao_t *s2) {
    solucao_t *p1=s1;
    solucao_t *p2=s2;

    while (p1 || p2) {

	if ((p1->pos_A != p2->pos_A) ||
	    (p1->pos_B != p2->pos_B))
	    return false;
	
	p1= p1->proximo;
	p2= p2->proximo;
    }
    
    return true;
}

    
static solucao_t *
procurar_solucao_linear_base(const char *origem, const size_t m, const char*destino, const size_t n, const double gap, penalidade_fn penalidade, size_t base_m,size_t base_n ){

    if (m<=2 || n<=2) 
	return procurar_solucao_base(origem,m,
				     destino,n,
				     gap,penalidade,
				     base_m,base_n);
    


        double ultimo_metade1[m+1];
    double corrente_metade1[m+1];
    double ultimo_metade2[m+1];
    double corrente_metade2[m+1];
    
    for (int i=0; i<=m; i++){
	corrente_metade1[i] = i*gap;
	corrente_metade2[m-i] = i*gap;
    }

    for (long j=1; j<=(long)n/2; j++) {	
	for (long i=0; i<=m; i++)
	    ultimo_metade1[i] = corrente_metade1[i];
	
	corrente_metade1[0] = j*gap;

	for (long i=1; i<=m; i++){

	    double val1=
		penalidade(origem[i-1],destino[j-1])
		+ ultimo_metade1[i-1];
	    double val2=gap + corrente_metade1[i-1];
	    double val3=gap + ultimo_metade1[i];

	    corrente_metade1[i] = min (val1, val2, val3);
	}
    }

    for(long j=n-1; j>=(long)n/2;j--) {
	for (long i=0; i<=m; i++)
	    ultimo_metade2[i] = corrente_metade2[i];
	
	corrente_metade2[m] = (n-j)*gap;
	for (long i=m-1; i>=0; i--){

	    double val1=
		penalidade(origem[i],destino[j])
		+ ultimo_metade2[i+1];
	    double val2=gap + corrente_metade2[i+1];
	    double val3=gap + ultimo_metade2[i];

	    corrente_metade2[i] = min (val1, val2, val3);

 	}

    }


    size_t j=0;
    double min_val = INFINITY; 

    for (int i =0; i<=min(m,n); i++){
	double val = corrente_metade1[i]+corrente_metade2[i];
	if (val <=min_val) {
	    min_val = val;
	    j=i;
	}
	    
    }
    /*
    fprintf(stderr, "     min_val: %f\n",min_val);
    fprintf(stderr, "   string1 : <%.*s>\n",(int)m,origem);
    fprintf(stderr, "   string1 : <%.*s><%.*s>\n",
	    (int)m/2, origem,
	    (int)(m-m/2), origem+m/2 );
    */
    solucao_t *sol_metade1 = procurar_solucao_linear_base(origem,m/2,
							  destino,j,
							  gap,penalidade,
							  base_m, base_n);
    solucao_t *sol_metade2 = procurar_solucao_linear_base(origem+(m/2),m-m/2,
							  destino+j,n-j,
							  gap,penalidade,
							  base_m+m/2, base_n+j);

    solucao_t * sol = solucao_merge(sol_metade1,sol_metade2);
    

    
    return sol;
}


solucao_t *
procurar_solucao_linear(const char *origem, const size_t m,
			const char*destino, const size_t n,
			const double gap, penalidade_fn penalidade) {
    
    return procurar_solucao_linear_base(origem,m,destino,n,gap,penalidade,0,0);
}

double
alinhamento_linear_custo2(const char *origem, size_t m, const char*destino, size_t n, double gap, penalidade_fn penalidade){

    double ultimo_metade1[m+1];
    double corrente_metade1[m+1];
    double ultimo_metade2[m+1];
    double corrente_metade2[m+1];
    
    for (int i=0; i<=m; i++){
	corrente_metade1[i] = i*gap;
	corrente_metade2[m-i] = i*gap;
    }

    for (long j=1; j<=(long)n/2; j++) {	
	for (long i=0; i<=m; i++)
	    ultimo_metade1[i] = corrente_metade1[i];
	
	corrente_metade1[0] = j*gap;

	for (long i=1; i<=m; i++){

	    double val1=
		penalidade(origem[i-1],destino[j-1])
		+ ultimo_metade1[i-1];
	    double val2=gap + corrente_metade1[i-1];
	    double val3=gap + ultimo_metade1[i];

	    corrente_metade1[i] = min (val1, val2, val3);
	}
    }

    for(long j=n-1; j>=(long)n/2;j--) {
	for (long i=0; i<=m; i++)
	    ultimo_metade2[i] = corrente_metade2[i];
	
	corrente_metade2[m] = (n-j)*gap;
	for (long i=m-1; i>=0; i--){

	    double val1=
		penalidade(origem[i],destino[j])
		+ ultimo_metade2[i+1];
	    double val2=gap + corrente_metade2[i+1];
	    double val3=gap + ultimo_metade2[i];

	    corrente_metade2[i] = min (val1, val2, val3);

 	}

    }
    
    double min_val= INFINITY ; 

    for (long i =0; i<=m; i++){
	double val = corrente_metade1[i]+corrente_metade2[i];
	if (val <=min_val) {
	    min_val = val;
	}
	    
    }

    return min_val;
}
