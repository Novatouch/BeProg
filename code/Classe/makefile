CC=gcc
CFLAGS=-Wall
EXEC=programme
all :$(EXEC)
asprintf.o : asprintf.h asprintf.c
	$(CC) $(CFLAGS) -c asprintf.c
ListeClient.o : ListeClient.h ListeClient.c
	$(CC) $(CFLAGS) -c ListeClient.c
Message.o : Message.h Message.c asprintf.h
	$(CC) $(CFLAGS) -c Message.c
ConnexionServeur.o : ConnexionServeur.h ConnexionServeur.c ListeClient.h
	$(CC) $(CFLAGS) -c ConnexionServeur.c
Serveur.o : Serveur.h Serveur.c ConnexionServeur.h ListeClient.h
	$(CC) $(CFLAGS) -c Serveur.c
TraitementServeur.o : TraitementServeur.h TraitementServeur.c Serveur.h ConnexionServeur.h Message.h
	$(CC) $(CFLAGS) -c TraitementClient.c
mainserveur.o : mainserveur.c Serveur.h TraitementServeur.h Serveur.h ConnexionServeur.h Message.h
	$(CC) $(CFLAGS) -c mainserveur.c
ConnexionClient.o : ConnexionClient.h ConnexionClient.c ListeClient.h
	$(CC) $(CFLAGS) -c ConnexionClient.c
Client.o : Client.h Client.c ConnexionClient.h ListeClient.h 
	$(CC) $(CFLAGS) -c Client.c
TraitementClient.o : TraitementClient.h TraitementClient.c Client.h ConnexionClient.h Message.h
	$(CC) $(CFLAGS) -c TraitementClient.c
mainclient.o : mainclient.c Client.h ConnexionClient.h TraitementClient.h Client.h ConnexionClient.h Message.h
	$(CC) $(CFLAGS) -c mainclient.c
$(EXEC) : asprintf.o ListeClient.o Message.o ConnexionServeur.o Serveur.o TraitementServeur.o mainserveur.o ConnexionClient.o Client.o TraitementClient.o mainclient.o
	$(CC) $(CFLAGS) asprintf.o ListeClient.o Message.o ConnexionServeur.o Serveur.o TraitementServeur.o mainserveur.o ConnexionClient.o Client.o TraitementClient.o mainclient.o -o $(EXEC)
clean :
	rm -f *~ *.o \#*
cleanall : clean
	rm -f $(EXEC)
