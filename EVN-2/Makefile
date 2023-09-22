all: main

main: main1.o complex.o
	g++ -o main main1.o complex.o

complex.o: complex.cpp complex.h
	g++ -c complex.cpp

main1.o: main1.cpp
	g++ -c main1.cpp

clean:
	rm *.o main
