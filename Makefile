P = trabalho2

OBJS = src/trab2.o 


CFLAGS = -Wall -g -std=c99 -Iinclude -O0 -fprofile-arcs -ftest-coverage
LDFLAGS = -Wall -g -std=c99 -fprofile-arcs 
LDLIBS = -lm -lgcov


all: $(P) $(P)_ut

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $< 

lib$(P).a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $<

$(P): src/main.o lib$(P).a
	$(CC) -o $@ $(LDFLAGS) $(LDLIBS) $< -L. -l${P}

$(P)_ut: src/tests.o lib$(P).a
	$(CC) -o $@ $(LDFLAGS) $(LDLIBS) $< -L. -l${P}

clean:
	rm -f *.o src/*.o
	rm -f src/*.gcno
	rm -f src/*.gcda
	rm -f *.c.gcov
	rm -f $(P) lib$(P).a $(P)_ut
