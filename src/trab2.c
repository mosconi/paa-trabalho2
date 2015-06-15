#include "trab2.h"


static double s_min(double list[]){
    double *p=list;
    double min=*p;
    while (!isnan(*p)){
	if (min > *p)
	    min = *p;
	p++;
    }
    return min;
}

#define min(...) s_min((double []){__VA_ARGS__,NAN})

double
alinhamento_quadratico_custo(char *origem,size_t m,  char*destino, size_t n, double gap, penalidade_fn penalidade){

    double M[m+1][n+1];
    
    for (int i=0; i<=m;i++){
	M[i][0]= i*gap;
    }
    for (int j=0; j<=n;j++){
	M[0][j]= j*gap;
    }

    for (int i=1; i<=m; i++) {
	for (int j=1; j<=n;j++){
	    double val1=penalidade(origem[i],destino[j]) + M[i-1][j-1];
	    double val2=gap + M[i-1][j];
	    double val3=gap + M[i][j-1];

	    M[i][j] = min(val1,val2,val3);
	}
    }
    return M[m][n];
}


double
alinhamento_linear_custo(char *origem, size_t m, char*destino, size_t n, double gap, penalidade_fn penalidade){
    double corrente[m];
    double ultimo[m];

    for (int i=0; i<=m; i++)
	corrente[i] = i*gap;


    for (int j=1; j<=n;j++) {	
	for (int i=0; i<=m; i++)
	    ultimo[i] = corrente[i];
	
	corrente[0] = j*gap;

	for (int i=0; i<=m; i++){
	    double val1=penalidade(origem[i],destino[j]) + ultimo[i-1];
	    double val2=gap + corrente[i-1];
	    double val3=gap + ultimo[i];

	    corrente[i] = min (val1, val2, val3);
	}
    }
    
    
    return corrente[m];
}
