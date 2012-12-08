#include <stdio.h>
#include <stdlib.h>

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

int main()
{
    // socket rendez vous
    int sockfd;
    // socket com avec client
    int sockd_com;

    // structure pour le serveur
    struct sockaddr_in  my_addr;

    // structure pour le client
    struct sockaddr_in addr_client;
    socklen_t addr_clientlen;

    // tampon réception
    char buffer_read[1024];

    // configuration de l'adresse
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    inet_aton("127.0.0.1",&(my_addr.sin_addr));
    memset(&(my_addr.sin_zero),'\0',8);

    // création du socket
    if((sockfd = socket (PF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("Erreur ouverture socket\n");
        exit(1);
    }


    // association adresse descripteur
    if ((bind(sockfd,(struct sockaddr *)&my_addr,sizeof(my_addr))==-1))
    {
        printf("Erreur association adresse descripteur\n");
        exit(1);
    }

    // mise en place file d'attente
    if (listen(sockfd,5)==-1)
    {
        printf("Erreur mise en place file d'attente\n");
        exit(1);
    }

    // attentee demande de connexion du client
    if ((sockd_com = accept(sockfd, (struct sockaddr *)&addr_client, &addr_clientlen)) == -1)
    {
        printf("Erreur acceptation de la demande de connexion\n");
        exit(1);
    }


    // attente d'un message du client
    if(read(sockd_com, buffer_read, 1024) == -1)
    {
        printf("Erreur réception message\n");
        exit(1);
    }



    // Affichage message client
    printf("message recu : %s",buffer_read);


    // envoi message
    if( write(sockd_com, "Salut client vive le C", 200) == -1)
    {
        printf("Erreur envoi message\n");
        exit(1);
    }



    // fermeture socket
    if (close(sockfd) == -1)
    {
        printf("Erreur fermeture socket rendez vous\n");
        exit(1);
    }

    if (close(sockd_com) == -1)
    {
        printf("Erreur fermeture socket com\n");
        exit(1);
    }

    return 0;
}
