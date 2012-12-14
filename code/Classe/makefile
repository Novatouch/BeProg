# définition des cibles particulières
.PHONY: clean, mrproper
 
# désactivation des règles implicites
.SUFFIXES:
 
# définition des variables
CC = gcc
CFLAGS = -W -Wall


# all
all: mainClient.o Client.o ConnexionClient.o
	$(CC) mainClient.o Client.o ConnexionClient.o -o Programme
 
mainClient.o: mainClient.c Client.h ConnexionClient.h
	$(CC) -c mainClient.c -o mainClient.o $(CFLAGS)
 
Client.o: Client.c
	$(CC) -c Client.c -o Client.o $(CFLAGS)
 
ConnexionClient.o: ConnexionClient.c
	$(CC) -c ConnexionClient.c -o ConnexionClient.o $(CFLAGS)	

# clean
clean:
	rm -rf *.bak rm -rf *.o
 
# mrproper
mrproper: clean
	rm -rf Programme
