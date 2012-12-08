#ifndef H_LISTE
#define H_LISTE

struct liste_client {
	unsigned int idClient;
	unsigned int idSession;
	unsigned int *next;
} liste_client;


int ajouterClient(liste_client *liste, unsigned int id);
int supprimerClient(liste_client *liste, unsigned int id);
int rechercherClient(liste_client *liste, unsigned int id);
#endif
