#include "trab2.h"

double gap = 0.7;

double
delta(char A, char B) {
    if (A == B)
	return 0;
    return 1.0;
};

double err= 0.01;

#define _TEST(fn,test,A,B,gap,delta,expected, error)     {	\
	test++;							\
	double val = fn(A,strlen(A),				\
			B,strlen(B),				\
			gap, delta);				\
	printf("  \"%s\", \"%s\" == %f : ",A,B,expected);	\
	if (fabs (val-expected) > error){			\
	    printf("nok (%f)\n",val);				\
	    return test;					\
	}							\
	printf ("ok\n");					\
    }								


int
main(void){

    int test=0;
    
    printf ("testes unitários -- custo quadratico\n");

    _TEST(alinhamento_quadratico_custo, test,"","",gap,delta,0.0,err);
    _TEST(alinhamento_quadratico_custo, test,"A","A",gap,delta,0.0,err);
    _TEST(alinhamento_quadratico_custo, test,"A","",gap,delta,0.7,err);
    _TEST(alinhamento_quadratico_custo, test,"A","B",gap,delta,1.0,err);
    _TEST(alinhamento_quadratico_custo, test,"AA","AA",gap,delta,0.0,err);
    _TEST(alinhamento_quadratico_custo, test,"AA"," AA",gap,delta,0.7,err);
    _TEST(alinhamento_quadratico_custo, test," A","AA",gap,delta,1.0,err);
    _TEST(alinhamento_quadratico_custo, test,"AA","BA",gap,delta,1.0,err);
    _TEST(alinhamento_quadratico_custo, test,"AB","BA",gap,delta,1.4,err);
    _TEST(alinhamento_quadratico_custo, test,"AB","CD",gap,delta,2.0,err);

    printf ("\ntestes unitários -- custo linear\n");

    _TEST(alinhamento_linear_custo, test,"","",gap,delta,0.0,err);
    _TEST(alinhamento_linear_custo, test,"A","A",gap,delta,0.0,err);
    _TEST(alinhamento_linear_custo, test,"A","",gap,delta,0.7,err);
    _TEST(alinhamento_linear_custo, test,"A","B",gap,delta,1.0,err);
    _TEST(alinhamento_linear_custo, test,"AA","AA",gap,delta,0.0,err);
    _TEST(alinhamento_linear_custo, test,"AA"," AA",gap,delta,0.7,err);
    _TEST(alinhamento_linear_custo, test," A","AA",gap,delta,1.0,err);
    _TEST(alinhamento_linear_custo, test,"AA","BA",gap,delta,1.0,err);
    _TEST(alinhamento_linear_custo, test,"AB","BA",gap,delta,1.4,err);
    _TEST(alinhamento_linear_custo, test,"AB","CD",gap,delta,2.0,err);
    
};
