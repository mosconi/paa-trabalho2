#include "trab2.h"

// HBD

bool print_memory_usage=false;

struct _solucao_t {
    size_t pos_A;
    size_t pos_B;
    struct _solucao_t *proximo;
};

// função para calcular o mínimo de uma lista terminada em NAN
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

// macro para converter arg variável em lista NAN terminada.
#define min(...) s_min((double []){__VA_ARGS__,NAN})



double 
opt_quadratico(const char *origem, const size_t m, const char* destino, const size_t n, const double gap, penalidade_fn penalidade){

    double M[m+1][n+1];

    double val = opt_quadratico_matriz(origem, m,  destino, n, gap, penalidade,M);

    return val;
}

double 
opt_quadratico_matriz(const char *origem, const size_t m,
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
opt_linear(const char *origem, size_t m, const char*destino, size_t n, double gap, penalidade_fn penalidade){
    double corrente[m+1];

    opt_linear_array(origem,m,destino,n,gap,penalidade,corrente);
    
    return corrente[m];
}

double
opt_linear_array(const char *origem, size_t m, const char*destino, size_t n, double gap, penalidade_fn penalidade,double array[m+1]){
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


/* método baseado nas transparencias de aulas

   retorna o opt mínimo e devolve a solução.

   exibe o uso de memória antes de terminar.
 */
double 
find_sol_quadratico(const char *origem, const size_t m,
		    const char*destino, const size_t n,
		    const double gap, penalidade_fn penalidade,
		    solucao_t **sol_p){
    double M[m+1][n+1];

    double val = opt_quadratico_matriz(origem, m,  destino, n, gap, penalidade,M);

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
	    *sol_p = NULL;
	    return 0.0;
	}
    }
    
    if(print_memory_usage)
	printf("    memoria (current): %zu\n", getCurrentRSS() );

    *sol_p = solucao;
    
    return val ;

}

static double
find_sol_base(const char *origem, const size_t m,
	      const char*destino, const size_t n,
	      const double gap, penalidade_fn penalidade,
	      size_t base_m,size_t base_n,
	      solucao_t **sol_p ){
    
    double M[m+1][n+1];

    double opt_val = opt_quadratico_matriz(origem, m,
					   destino, n,
					   gap, penalidade, M);

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
	    *sol_p = NULL;
	    return 0;
	}
    }

    *sol_p = solucao;
    
    return opt_val;

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

    if (!s1 && !s2)
	return true;

    if (!s1 || !s2)
	return false;

    while (p1 || p2) {

	if ((p1->pos_A != p2->pos_A) ||
	    (p1->pos_B != p2->pos_B))
	    return false;
	
	p1= p1->proximo;
	p2= p2->proximo;
    }
    
    return true;
}



/*
  Algoritmo baseado em 
  http://par.cse.nsysu.edu.tw/~wuys/Hirschberg%20Algorithm%20C(Divide%20and%20Conquer,%201975).html

  Este algoritmo computa o melhor caminho de (0,0) até a linha N/2 e de (m,n) até a linha N/2. Em 
  sequida localiza a coluna 0 <= k <= M que minimiza a solução.

  Invoca find_sol_linear_base() no para as regiões (0,0) <=> (k,N/2) e (k,N/2) <=> (M,N).  

  devolve a união (concat) das duas e retorna o opt mínimo.

  Este método não exibe o úso de memória correte, pois como é um método recursivo, 
  cada invocaçào mostraria o uso, poluindo assim a saída.

  HDGRWD 
*/
static double
find_sol_linear_base(const char *origem, const size_t m,
		     const char*destino, const size_t n,
		     const double gap, penalidade_fn penalidade,
		     size_t base_m,size_t base_n ,
		     solucao_t **sol_p){

    /*
      para valores pequenos de m ou n, o consumo de memória é similar.

      Caso m<=2 ou n<=2, será usado a procura quadratica.
    */
    if (m<=2 || n<=2) 
	return find_sol_base(origem,m,
			     destino,n,
			     gap,penalidade,
			     base_m,base_n,
			     sol_p);
    
    /* 
       vetores que armazanearam a lista corremte e última de cada metada.

       como estamos usando um vetor em M, a tabela será percorrida em N

     */

    double ultimo_metade1[m+1];
    double corrente_metade1[m+1];
    double ultimo_metade2[m+1];
    double corrente_metade2[m+1];

    // inicializando o primeiro correte com gaps somente.
    for (int i=0; i<=m; i++){
	corrente_metade1[i] = i*gap;
	corrente_metade2[m-i] = i*gap;
    }

    /*
      calculando a primeira metade: "linhas" 0-> N/2
     */
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
    
    /*
      calculando a segunda metade: "linhas" N-> N/2

      Nesta parte a "tabela" é percorrida ao contrário.
      
      Vai do maior M,N até o (0,N/2).


      vale ressaltar que a linha N/2 é processada 2 vezes
      tanto na primeira parte, quando na segunda.
    */

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


    /*
      Localizando a coluna 
     */
    size_t j=0;
    double min_val = INFINITY; 

    for (int i =0; i<=m; i++){
	double val = corrente_metade1[i]+corrente_metade2[i];
	if (val <=min_val) {
	    min_val = val;
	    j=i;
	}
	    
    }

    solucao_t *sol_metade1 = NULL;
    find_sol_linear_base(origem,m/2,
			 destino,j,
			 gap,penalidade,
			 base_m, base_n,
			 &sol_metade1);
    
    solucao_t *sol_metade2 =NULL;
    
    find_sol_linear_base(origem+(m/2),m-m/2,
			 destino+j,n-j,
			 gap,penalidade,
			 base_m+m/2, base_n+j,
			 &sol_metade2);

    *sol_p = solucao_merge(sol_metade1,sol_metade2);
    

    
    return min_val;
}

/*
  find_sol_linear pública, invoca o método recursivo.
*/

double
find_sol_linear(const char *origem, const size_t m,
		const char*destino, const size_t n,
		const double gap, penalidade_fn penalidade,
		solucao_t **sol_p) {
    
    return find_sol_linear_base(origem,m,destino,n,gap,penalidade,0,0,sol_p);
}

/*
  Algoritmo baseado em 
  http://par.cse.nsysu.edu.tw/~wuys/Hirschberg%20Algorithm%20C(Divide%20and%20Conquer,%201975).html

  Este algoritmo computa o melhor caminho de (0,0) até a linha N/2 e de (m,n) até a linha N/2. Em 
  sequida localiza a coluna 0 <= k <= M que minimiza a solução.

*/

double
opt_linear2(const char *origem, size_t m,
	    const char*destino, size_t n,
	    double gap, penalidade_fn penalidade){

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
