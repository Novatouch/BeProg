#ifndef __SERVEUR_H__
#define __SERVEUR_H__

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
    int sockfd;
    int sockd_com;
    struct sockaddr_in  my_addr;
    struct sockaddr_in addr_client;
    socklen_t addr_clientlen;
    char *adresse;
    int port;
}config_connex;

int initialisationConnexion(config_connex *config, char *adresse, int port);
int miseEnEcoute(config_connex *config);
int attenteConnexionClient(config_connex *config);
int envoiMessage(config_connex *config, char *message);
int receptionMessage(config_connex *config, char *message);
int envoiBinaire(config_connex *config, char *message, size_t taille);
int receptionBinaire(config_connex *config, char **message, size_t taille);
int fermeture(config_connex *config);
#endif
