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
    
    printf ("\ntestes unitários -- custo quadratico\n");

    _TEST(opt_quadratico, test,"","",gap,delta,0.0,err);
    _TEST(opt_quadratico, test,"A","A",gap,delta,0.0,err);
    _TEST(opt_quadratico, test,"A","",gap,delta,0.7,err);
    _TEST(opt_quadratico, test,"A","B",gap,delta,1.0,err);
    _TEST(opt_quadratico, test,"AA","AA",gap,delta,0.0,err);
    _TEST(opt_quadratico, test,"AA"," AA",gap,delta,0.7,err);
    _TEST(opt_quadratico, test," A","AA",gap,delta,1.0,err);
    _TEST(opt_quadratico, test,"AA","BA",gap,delta,1.0,err);
    _TEST(opt_quadratico, test,"AB","BA",gap,delta,1.4,err);
    _TEST(opt_quadratico, test,"AB","CD",gap,delta,2.0,err);
    _TEST(opt_quadratico, test,"AAA","AAA",gap,delta,0.0,err);
    _TEST(opt_quadratico, test,"AAA","ABA",gap,delta,1.0,err);
    _TEST(opt_quadratico, test,"AAA","AAA",gap,delta,0.0,err);
    _TEST(opt_quadratico, test,"AAA","ABA",gap,delta,1.0,err);
    _TEST(opt_quadratico, test,"AAAA","AAAA",gap,delta,0.0,err);
    _TEST(opt_quadratico, test,"AAAA","AABA",gap,delta,1.0,err);
    _TEST(opt_quadratico, test,"BABACA","BANANA",gap,delta,2.0,err);
    _TEST(opt_quadratico, test,"CABANA","BACANA",gap,delta,2.0,err);

    printf ("\ntestes unitários -- custo linear\n");

    _TEST(opt_linear, test,"","",gap,delta,0.0,err);
    _TEST(opt_linear, test,"A","A",gap,delta,0.0,err);
    _TEST(opt_linear, test,"A","",gap,delta,0.7,err);
    _TEST(opt_linear, test,"A","B",gap,delta,1.0,err);
    _TEST(opt_linear, test,"AA","AA",gap,delta,0.0,err);
    _TEST(opt_linear, test,"AA"," AA",gap,delta,0.7,err);
    _TEST(opt_linear, test," A","AA",gap,delta,1.0,err);
    _TEST(opt_linear, test,"AA","BA",gap,delta,1.0,err);
    _TEST(opt_linear, test,"AB","BA",gap,delta,1.4,err);
    _TEST(opt_linear, test,"AB","CD",gap,delta,2.0,err);
    _TEST(opt_linear, test,"AAA","AAA",gap,delta,0.0,err);
    _TEST(opt_linear, test,"AAA","ABA",gap,delta,1.0,err);
    _TEST(opt_linear, test,"AAA","AAA",gap,delta,0.0,err);
    _TEST(opt_linear, test,"AAA","ABA",gap,delta,1.0,err);
    _TEST(opt_linear, test,"AAAA","AAAA",gap,delta,0.0,err);
    _TEST(opt_linear, test,"AAAA","AABA",gap,delta,1.0,err);
    _TEST(opt_linear, test,"BABACA","BANANA",gap,delta,2.0,err);
    _TEST(opt_linear, test,"CABANA","BACANA",gap,delta,2.0,err);

    printf ("\ntestes unitários -- custo linear com corte\n");

    _TEST(opt_linear2, test,"","",gap,delta,0.0,err);
    _TEST(opt_linear2, test,"A","A",gap,delta,0.0,err);
    _TEST(opt_linear2, test,"A","",gap,delta,0.7,err);
    _TEST(opt_linear2, test,"A","B",gap,delta,1.0,err);
    _TEST(opt_linear2, test,"AA","AA",gap,delta,0.0,err);
    _TEST(opt_linear2, test,"AA"," AA",gap,delta,0.7,err);
    _TEST(opt_linear2, test," A","AA",gap,delta,1.0,err);
    _TEST(opt_linear2, test,"AA","BA",gap,delta,1.0,err);
    _TEST(opt_linear2, test,"AB","BA",gap,delta,1.4,err);
    _TEST(opt_linear2, test,"AB","CD",gap,delta,2.0,err);
    _TEST(opt_linear2, test,"AAA","AAA",gap,delta,0.0,err);
    _TEST(opt_linear2, test,"AAA","ABA",gap,delta,1.0,err);
    _TEST(opt_linear2, test,"AAA","AAA",gap,delta,0.0,err);
    _TEST(opt_linear2, test,"AAA","ABA",gap,delta,1.0,err);
    _TEST(opt_linear2, test,"AAAA","AAAA",gap,delta,0.0,err);
    _TEST(opt_linear2, test,"AAAA","AABA",gap,delta,1.0,err);
    _TEST(opt_linear2, test,"BABACA","BANANA",gap,delta,2.0,err);
    _TEST(opt_linear2, test,"CABANA","BACANA",gap,delta,2.0,err);
    
    printf ("\ntestes unitários -- classe de solucão\n");

    printf ("new(0,0,NULL): ");
    solucao_t *t = solucao_new(0,0,NULL);
    if (!t) {
	printf ("nok\n");
	return ++test;
    }
    
    printf("ok\n");
    
    printf ("destroy: ");
    solucao_destroy(&t);
    if (t) {
	printf ("nok\n");
	return ++test;
    }
    printf("ok\n");

    printf ("new(0,0,NULL): ");
    t = solucao_new(0,0,NULL);
    if (!t) {
	printf ("nok\n");
	return ++test;
    }
    printf("ok\n");
        printf ("new(1,1,t): ");
    t = solucao_new(1,1,t);
    if (!t) {
	printf ("nok\n");
	return ++test;
    }
    printf("ok\n");

    solucao_print(t);
    solucao_destroy(&t);

    printf ("\ntestes de uso\n");

    solucao_t *ref = NULL;
    ref = solucao_new(3,3, ref);
    ref = solucao_new(2,2, ref);
    ref = solucao_new(1,1, ref);
    ref = solucao_new(0,0, ref);


    printf ("\"ABCD\", \"ABCD\" == 0.0 via (0,0) (1,1) (2,2) (3,3):");
    double val =  find_sol_quadratico("ABCD",4,"ABCD",4,gap,delta,&t);
    assert ( abs(val - 0) <err);
    assert ( solucao_eq(ref, t)); 

    solucao_destroy(&t);
    solucao_destroy(&ref);
    printf (" ok\n");

    ref = solucao_new(3,2, ref);
    ref = solucao_new(2,1, ref);
    ref = solucao_new(1,0, ref);
    
    printf ("\"ABCD\", \"BCD\"  == 0.7 via (1,0) (2,1) (3,2):");
    val = find_sol_quadratico("ABCD",4,"BCD",3,gap,delta, &t);
    assert( abs(val - gap) <err);
    assert ( solucao_eq(ref, t)); 
    solucao_destroy(&t);
    solucao_destroy(&ref);
    printf (" ok\n");

    ref = solucao_new(3,3, ref);
    ref = solucao_new(2,2, ref);
    ref = solucao_new(1,1, ref);
    ref = solucao_new(0,0, ref);

    printf ("\"AAAA\", \"ABCD\" == 3.0 via (0,0) (1,1) (2,2) (3,3):");
    val = find_sol_quadratico("AAAA",4,"ABCD",4,gap,delta, &t);
    assert( abs(val - 3.0) <err);
    assert ( solucao_eq(ref, t)); 
    solucao_destroy(&t);
    solucao_destroy(&ref);
    printf (" ok\n");

};
