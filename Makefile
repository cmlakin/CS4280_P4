#Corrina Lakin CS4280 P0

CC = g++
CFLAGS = -g -Wall -std=c++11
OBJS = main.o parser.o scanner.o treePrint.o statSem.o codeGen.o


codeGen: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o codeGen

main.o: main.cpp parser.h scanner.h token.h treePrint.h statSem.h codeGen.h
	$(CC) $(CFLAGS) -c main.cpp

scanner.o: scanner.cpp scanner.h token.h
	$(CC) $(CFLAGS) -c scanner.cpp

parser.o: parser.cpp parser.h statSem.h
	$(CC) $(CFLAGS) -c parser.cpp

treePrint.o: treePrint.cpp treePrint.h
	$(CC) $(CFLAGS) -c treePrint.cpp

statSem.o: statSem.cpp statSem.h
	$(CC) $(CFLAGS) -c statSem.cpp

codeGen.o: codeGen.cpp codeGen.h
	$(CC) $(CFLAGS) -c codeGen.cpp

clean:
	rm *.o codeGen
