CC=g++ $(CFLAGS)
CFLAGS=-std=c++11
tictactoe: main.o
	$(CC) main.o -o tictactoe.bin

main.o: main.cpp
	$(CC) -c main.cpp

clean:
	rm *.o tictactoe.bin