#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>

#define _GNU_SOURCE
#include "Serveur.h"
#include "ConnexionServeur.h"
#include "TraitementServeur.h"

int main()
{
    config_connex connex_serveur;
    pid_t pid;
    char chaine[TAILLE_BUFFER];


    printf("Initialisation serveur ...\n");
    if( (initialisationConnexion(&connex_serveur, "127.0.0.1", MYPORT)) != 0){

        printf("erreur intialisation structure connexion\n");
        return 1;
    }

    if( (miseEnEcoute(&connex_serveur) != 0)){

        printf("erreur mise en ecoute\n");
        return 1;
    }

    printf("Mise en écoute du serveur ...\n");

    while(1){

        printf("Attente de connexion d'un client ...\n");

        if( (attenteConnexionClient(&connex_serveur)) != 0){

            printf("Erreur lors de l'attente de connexion d'un client\n");
            return 1;
        }

        pid = fork();

        if (pid == -1) {

            /* erreur - impossible de créer un fils */

            perror("fork error\n");
            return 1;

        }
        else if (pid == 0) {

            //code du fils
            printf("processus FILS >>>> fork\n");
            close(connex_serveur.sockfd);

            if( (receptionMessage(&connex_serveur, chaine)) != 0){

                printf("Erreur lors de l'attente de connexion d'un client\n");

                if(traitementRequete(chaine)){

                    printf("Erreur lors du traitement de la requête\n");
                    return 0;
                }

               return 1;
            }
        }
        else{

            //code du père
            printf("processus PERE >>>> fork\n");
            close(connex_serveur.sockd_com);

        }
    }

    if( (fermeture(&connex_serveur)) != 0){

        printf("Erreur lors de la fermeture de la connexion \n");
        return 1;
    }

	return 0;
}
