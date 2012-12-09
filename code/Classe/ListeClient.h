#ifndef H_LISTE
#define H_LISTE

typedef struct case_liste_client case_liste_client;
struct case_liste_client {
	unsigned int idClient;
	unsigned int idSession;
	unsigned int *next;
	unsigned int *prev;
};

typedef struct liste_client liste_client;
struct liste_client
{
    case_liste_client *first;
    case_liste_client *last;
};

int ajouterClient(liste_client *liste, unsigned int id);
int supprimerClient(liste_client *liste, unsigned int id);
int rechercherClient(liste_client *liste, unsigned int id);
#endif
