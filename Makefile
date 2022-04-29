#Corrina Lakin CS4280 P4

CC = g++
CFLAGS = -g -Wall -std=c++11
OBJS = main.o parser.o scanner.o treePrint.o statSem.o genCode.o


genCode: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o genCode

main.o: main.cpp parser.h scanner.h token.h treePrint.h statSem.h genCode.h
	$(CC) $(CFLAGS) -c main.cpp

scanner.o: scanner.cpp scanner.h token.h
	$(CC) $(CFLAGS) -c scanner.cpp

parser.o: parser.cpp parser.h statSem.h
	$(CC) $(CFLAGS) -c parser.cpp

treePrint.o: treePrint.cpp treePrint.h
	$(CC) $(CFLAGS) -c treePrint.cpp

statSem.o: statSem.cpp statSem.h
	$(CC) $(CFLAGS) -c statSem.cpp

genCode.o: genCode.cpp genCode.h
	$(CC) $(CFLAGS) -c genCode.cpp

clean:
	rm *.o genCode
