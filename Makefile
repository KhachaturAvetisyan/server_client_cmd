CC = g++

all:
	$(CC) server.cpp -o server.o
	$(CC) client.cpp -lreadline -o client.o

clean:
	rm -rf *.o