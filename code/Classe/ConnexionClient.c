

#include "ConnexionClient.h"

/*
	auteur : Philippe GAUTIER
	but : Création Socket et connexion au serveur
	paramètres : struct config_connex, hostname le nom du serveur, le port
	renvoi : 0 OK 1 NOK
*/

int connexionServeur(config_connex *config, char *hostname, int port)
{
    config->hostinfo = NULL;
    //config->sin = { 0 };

    // initialisation socket
    config->socket = socket(AF_INET, SOCK_STREAM, 0);
    if(config->socket == -1){
        perror("socket()");
        return 1;
    }

    config->hostinfo  = gethostbyname(hostname); /* on récupère les informations de l'hôte auquel on veut se connecter */

    /* l'hôte n'existe pas */
    if (config->hostinfo == NULL) {
        fprintf (stderr, "hote inconnu host %s.\n", hostname);
        return 1;
    }

    config->sin.sin_addr = *(struct in_addr *) config->hostinfo->h_addr; /* l'adresse se trouve dans le champ h_addr de la structure hostinfo */
    config->sin.sin_port = htons(port); /* on utilise htons pour le port */
    config->sin.sin_family = AF_INET;


    if(connect(config->socket,(struct sockaddr *) &config->sin, sizeof(struct sockaddr)) == -1){
        perror("connect()");
        return 1;
    }

    return 0;
}


/*
	auteur : Philippe GAUTIER
	but : Création Socket et connexion au serveur
	paramètres : struct config_connex, message à envoyer
	renvoi : 0 OK 1 NOK
*/
int envoiRequete(config_connex *config, char *message)
{
    // vérification longeur requête
    if(strlen(message) > TAILLE_BUFFER){
        printf ("Longeur message trop grand.\n");
        return 1;
    }

    if(send(config->socket, message, strlen(message), 0) < 0){
        printf ("Erreur lors de l'envoi de donnée.\n");
        return 1;
    }

    return 0;
}

int receptionRequete(config_connex *config, char *message)
{

    int n;

    if( (n = read(config->socket, message, TAILLE_BUFFER-1)) < 0){
        printf("Erreur réception message\n");
        return 1;
    }

    message[n] = '\0';

    return 0;
}

int fermetureConnexion(config_connex *config)
{
    close(config->socket);

    return 0;
}
