P = trabalho2
T2A = tarefa2a
T2B = tarefa2b
OBJS = src/trab2.o
OBJS+= src/graph.o
OBJS+= src/list.o
OBJS+= src/set.o 	

DEBUG_FLAGS = -g -O0
#DEBUG_FLAGS =
RELEASE = -s -Os -O3

CFLAGS = -Wall  -std=c99 -Iinclude -pthread -Werror -Wno-unused-variable $(DEBUG_FLAGS)
LDFLAGS = -Wall -g -std=c99 -Werror -pthread  $(DEBUG_FLAGS)
LDLIBS = -lm -lgcov -lrt -lprocps


all: $(P) $(P)_ut $(T2A) $(T2B)

.c.o: 
	$(CC) -c $(CFLAGS) -o $@ $< 

lib$(P).a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $^ 

$(P): src/main.o lib$(P).a
	$(CC) -o $@ $(LDFLAGS) $(LDLIBS) $^

$(P)_ut: src/tests.o lib$(P).a
	$(CC) -o $@ $(LDFLAGS) $(LDLIBS) $^ 

$(T2A): $(P)
	ln -f $< $@

$(T2B): $(P)
	ln -f $< $@


package: $(P).tgz
tgz: $(P).tgz

$(P).tgz: Makefile include/*.h src/*.c
	tar -czf $@ Makefile src include

clean:
	rm -f *.o src/*.o
	rm -f $(P) lib$(P).a $(P)_ut  $(T2A) $(T2B)
	rm -f $(P).tgz

test: $(P)_ut
	./$(P)_ut
