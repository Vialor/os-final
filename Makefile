CXX := gcc
PROG := run run2 caching fast system_call

all: $(PROG)
	make run
	make run2
	make caching
	make fast

# Part 1
run: run.o rdwr.o tools.o
	$(CXX) -o run run.o rdwr.o tools.o
# Part 2,3
run2: run2.o rdwr.o tools.o
	$(CXX) -o run2 run2.o rdwr.o tools.o
# Part 4
caching: caching.o rdwr.o tools.o
	$(CXX) -o caching caching.o rdwr.o tools.o
# Part 5
system_call: system_call.o rdwr.o tools.o
	$(CXX) -o system_call system_call.o rdwr.o tools.o
# Part 6
fast: fast.o
	$(CXX) -o fast fast.o

%.o: %.c
	$(CXX) -c $< $@

.PHONY: clean
clean:
	rm -f *.o $(PROG)