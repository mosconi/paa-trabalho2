#include "trab2.h"


pthread_mutex_t calculating = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t done = PTHREAD_COND_INITIALIZER;

#define MIN_TO_SEG 60

#define _TIMEOUT_15_MIN 15 * MIN_TO_SEG

#define strarg(s) s, strlen(s)

static const char *VALID_CHARS="ABCD";

extern char *__progname;

double gap = 0.7;

double
delta(char A, char B) {
    if (A == B)
	return 0;
    return 1.0;
};


static void
usage(void){
    printf ("usage:\n");
    printf ("  tarefa2a [-i <val>] [-b <start_val>] [-e <stop_val>]\n");
    printf ("  tarefa2b -blq [-s val] [-m val]\n");
    
}


static size_t
ipow (size_t base, size_t i) {
    size_t hi = i/2;
    size_t pre = i%2? base: 1;

    if (i==1)
	return base;
    
    size_t val = ipow ( base, hi);
    
    return pre * val *val ;
}

static char **
generate (size_t size) {
    assert(size >0);
    char **str = calloc(sizeof(char *),2);

    if (!str)
	goto ERROR;
    
    str[0] = calloc(size+1,1);
    if (!str[0])
	goto ERROR;
    
    str[1] = calloc(size+1,1);
    if (!str[1])
	goto ERROR;
    
    size_t l = strlen(VALID_CHARS);

    srand(time(NULL));
    for (long long i = 0; i<size; i++) {
	str[0][i] = VALID_CHARS[rand()%l];
	str[1][i] = VALID_CHARS[rand()%l];
    }
    return str;
 ERROR:
    if (str[1])
	free(str[1]);
    if (str[1])
    	free(str[0]);
    free(str);
    return NULL;
}
/*
void *
pthread_wrapper(void *data) {
    assert (data);
    char **strings = data;
    
};

static int
do_or_timeout(struct timespec max_wait) {

	return 0
}
*/

static int
tarefa2a(int argc, char **argv){


    int opt;

    int run_i=-1;
    int j_start =1 ;
    int j_stop = 10;

    while ((opt=getopt(argc,argv,"i:b:e:")) != -1) {
	switch (opt) {
	case 'i':
	    run_i = atoi(optarg);
	    break;
	case 'b':
	    j_start = atoi(optarg);
	    break;
	case 'e':
	    j_start = atoi(optarg);
	    break;
	default: // '?'
	    usage();
	    return -1;
	}
    }
    
    for (int i = run_i>0? run_i : 1;
	 i <= (run_i>0? run_i : 14);
	 i++) 
	for (int j = j_start; j<=j_stop; j++) {
	    fprintf (stderr, "TODO i= %d, j=%d...\n", i, j);
	}
    
    return 0;
    
}

static int
tarefa2b(int argc, char **argv){

    if (argc<2) {
	usage ();
	return -1;
    }
    
    bool run_linear=false;
    bool run_quad=false;
    int timeout = _TIMEOUT_15_MIN;

    int opt;
    
    while ((opt=getopt(argc,argv,"blqsm")) != -1) {
	switch (opt) {
	case 's':
	    timeout = atoi(optarg) ;
	    break;
	case 'm':
	    timeout = atoi(optarg) * MIN_TO_SEG;
	    break;
	case 'b':
	    run_linear=true;
	    run_quad=true;
	    break;
	case 'l':
	    run_linear=true;
	    run_quad=false;
	    break;
	case 'q':
	    run_linear=false;
	    run_quad=true;
	    break;
	default:
	    usage();
	    return -1;
	}
    }

    struct timespec max_wait;
    
    memset(&max_wait, 0, sizeof(max_wait));
    
    max_wait.tv_sec = timeout;

    
    bool run = true;
    for (int i = 1; run; i++) {
	char **strings = generate(ipow(2,i));
	if (!strings) return -2;
	
	if (run_linear) {
	    /*
	      do_or_timeout(&max_wait);
	    solucao_t *t = procurar_solucao_linear(strarg(strings[0]),
						strarg(strings[1]),
						gap,delta);
	    solucao_destroy(&t);
	    */
	    
	}
	if (run_quad) {
	    /*
	    solucao_t *t = procurar_solucao_linear(strarg(strings[0]),
						   strarg(strings[0]),
						   gap,delta);
	    solucao_destroy(&t);
	    */
	}
	free (strings);
	    
    }
    
    return 0;
}
/*
static int
testsz (int argc, char **argv){
    printf("sizeof:\n");
    printf("size_t = %zu\n",sizeof(size_t));
    printf("int = %zu\n",sizeof(int));
    printf("long int = %zu\n",sizeof(long int));
    printf("__int128_t = %zu\n",sizeof(__int128_t));
    return 0;
}
*/
static int
test_generate(int argc, char **argv){

    if (argc <2 )
	return -1;
    
    int opt;
    int i=1;
    while ((opt=getopt(argc,argv,"i:")) != -1) {
	switch (opt) {
	case 'i':
	    i = atoi(optarg);
	    break;
	default:
	    usage();
	    return -1;
	}
    }

    size_t sz = ipow(2,i);
    char **strings = generate(sz);
    for (int k = 0; k <2; k++)
	printf("string %d:\n---- BEGIN ----\n%s\n---- END ----\n\n",
	       k+1, strings[k]);
	
    free(strings[0]);
    free(strings[1]);
    free(strings);
    return 0;
}

int
main(int argc, char **argv){

    int rc=-1;

    if (streq("trabalho2",__progname)) {
	--argc; ++argv;
    }
    if (
	streq("tarefa2a",__progname) ||
	streq("tarefa2a",argv[0]))
	rc = tarefa2a(argc,argv);

    else if (
	     streq("tarefa2b",__progname) ||
	     streq("tarefa2b",argv[0]))

	rc = tarefa2b(argc,argv);
    /*
    else if (
	     streq("testsz",__progname) ||
	     streq("testsz",argv[0]))

	rc = testsz(argc,argv);
    */
    else if (
	     streq("test",__progname) ||
	     streq("test",argv[0]) ||
	     streq("generate",__progname) ||
	     streq("generate",argv[0]))
	rc = test_generate(argc,argv);


    else 
	usage();

    return rc;
}
