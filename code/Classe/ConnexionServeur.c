#include "ConnexionServeur.h"
#include <stdio.h>
#include <stdlib.h>

/*
	auteur : Philippe GAUTIER
	but : initialiser les variables dans la structure de configuration connexion
	paramètres : struct config_connex
	renvoi : 0 OK 1 NOK

*/

int initialisationConnexion(config_connex *config, char *adresse, int port)
{
    config->port = port;

    return 0;
}



/*
	auteur : Philippe GAUTIER
	but : Création Socket et création del a file d'attente
	paramètres : struct config_connex
	renvoi : 0 OK 1 NOK
*/
int miseEnEcoute(config_connex *config)
{
    // configuration de l'adresse
    config->my_addr.sin_family = AF_INET;
    config->my_addr.sin_port = htons(config->port);

    // ecoute sur toutes les adresses
    config->my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(&(config->my_addr.sin_zero),'\0',8);

    if((config->sockfd = socket (PF_INET, SOCK_STREAM, 0)) == -1){
        printf("Erreur ouverture socket\n");
        return 1;
    }


    // association adresse descripteur
    if ((bind(config->sockfd,(struct sockaddr *)&config->my_addr,sizeof(config->my_addr))==-1)){
        printf("Erreur association adresse descripteur\n");
        return 1;
    }

    // mise en place file d'attente
    if (listen(config->sockfd,5)==-1){

        printf("Erreur mise en place file d'attente\n");
        return 1;
    }

    return 0;
}

/*
	auteur : Philippe GAUTIER
	but : attente de la connexion d'un client
	paramètres : struct config_connex
	renvoi :

*/

int attenteConnexionClient(config_connex *config)
{

    if ((config->sockd_com = accept(config->sockfd, (struct sockaddr *)&config->addr_client, &config->addr_clientlen)) == -1){

        printf("Erreur acceptation de la demande de connexion\n");
        return 1;
    }

    return 0;
}



int envoiMessage(config_connex *config, char *message)
{

    if( strlen(message) > TAILLE_BUFFER)
    {
        printf("La taille du message depasse le buffer\n");
        return 1;
    }

    if( send(config->sockd_com, message, strlen(message), 0) < 0)
    {
        printf("Erreur envoi message\n");
        return 1;
    }

    return 0;
}

int receptionMessage(config_connex *config, char *message)
{
    if (( message = malloc(TAILLE_BUFFER)) == NULL)
        return 1;


    if(recv(config->sockd_com, message, TAILLE_BUFFER, 0) < 0)
    {
        printf("Erreur réception message\n");
        return 1;
    }

    return 0;
}


int envoiBinaire(config_connex *config, char *message, size_t taille)
{

    if( write(config->sockd_com, message, taille) == -1)
    {
        printf("Erreur envoi Fichier\n");
        return 1;
    }

    return 0;

}

int receptionBinaire(config_connex *config, char **message, size_t taille)
{
    if (( config->adresse = malloc(taille)) == NULL)
        return 1;


    if(read(config->sockd_com, message, taille) == -1)
    {
        printf("Erreur réception Fichier\n");
        return 1;
    }

    return 0;
}

int fermeture(config_connex *config)
{
    if (close(config->sockfd) == -1)
    {
        printf("Erreur fermeture socket rendez vous\n");
        return 1;
    }

    if (close(config->sockd_com) == -1)
    {
        printf("Erreur fermeture socket com\n");
        return 1;
    }

    return 0;
}
