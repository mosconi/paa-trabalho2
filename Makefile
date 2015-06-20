P = trabalho2

OBJS = src/trab2.o
OBJS+= src/graph.o
OBJS+= src/list.o 


CFLAGS = -Wall -g -std=c99 -Iinclude -O0  -Werror
LDFLAGS = -Wall -g -std=c99 -Werror
LDLIBS = -lm -lgcov  -L. -l${P}


all: $(P) $(P)_ut

.c.o: %.h
	$(CC) -c $(CFLAGS) -o $@ $< 

lib$(P).a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $^ 

$(P): src/main.o lib$(P).a
	$(CC) -o $@ $(LDFLAGS) $(LDLIBS) $^

$(P)_ut: src/tests.o lib$(P).a
	$(CC) -o $@ $(LDFLAGS) $(LDLIBS) $^ 

clean:
	rm -f *.o src/*.o
	rm -f src/*.gcno
	rm -f src/*.gcda
	rm -f *.c.gcov
	rm -f $(P) lib$(P).a $(P)_ut

test: $(P)_ut
	./$(P)_ut


