CXX = gcc

run: run.o rdwr.o
	$(CXX) -o run run.o rdwr.o

run2: run2.o rdwr.o
	$(CXX) -o run2 run2.o rdwr.o

fast: fast.o
	$(CXX) -o fast fast.o

run.o: run.c
	$(CXX) -c run.c

run2.o: run2.c
	$(CXX) -c run2.c

fast.o: fast.c
	$(CXX) -c fast.c

rdwr.o: rdwr.c
	$(CXX) -c rdwr.c
