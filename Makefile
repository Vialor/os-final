CXX := gcc
PROG := run run2 caching fast

all: $(PROG)
	make run
	make run2
	make caching
	make fast

run: run.o rdwr.o tools.o
	$(CXX) -o run run.o rdwr.o tools.o

run2: run2.o rdwr.o tools.o
	$(CXX) -o run2 run2.o rdwr.o tools.o

caching: caching.o rdwr.o tools.o
	$(CXX) -o caching caching.o rdwr.o tools.o

fast: fast.o
	$(CXX) -o fast fast.o

%.o: %.c
	$(CXX) -c $< $@

.PHONY: clean
clean:
	rm -f *.o $(PROG)