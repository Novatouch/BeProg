#ifndef __CLIENTCONNECTION_H__
#define __CLIENTCONNECTION_H__


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>


// déclaration des types basiques
#include <sys/types.h>
// constantes concernant les domaines, les types et les protocoles
#include <sys/socket.h>
// constantes et structures propres au domaine INTERNET
#include <netinet/in.h>
// structures utilisées par les primitives de gestion de la base de données réseau
#include <netdb.h>
#include <arpa/inet.h>
// pour fonction memset
#include <string.h>
#include <unistd.h>

#define MYPORT 20000
#define TAILLE_BUFFER 300




typedef struct config_connex{
    int socket;
    struct hostent *hostinfo;
    struct sockaddr_in sin;
    int port;
}config_connex;

int connexionServeur(config_connex *config, char *hostname, int port);
int envoiRequete(config_connex *config, char *message);
int receptionRequete();
//int envoiBinaire();
//int receptionBinaire();
int fermetureConnexion(config_connex *config);

#endif
