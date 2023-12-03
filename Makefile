CXX = gcc

run: run.o rdwr.o
	$(CXX) -o run run.o rdwr.o

run2: run2.o rdwr.o
	$(CXX) -o run2 run2.o rdwr.o

run.o: run.c
	$(CXX) -c run.c

run2.o: run2.c
	$(CXX) -c run2.c

rdwr.o: rdwr.c
	$(CXX) -c rdwr.c

