#ifndef H_LISTE
#define H_LISTE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct liste *liste_client;

liste_client initilisation();

int ajouterClient(liste_client l, unsigned int id);

bool listeVide(liste_client l);

int supprimerClient(liste_client l, unsigned int id);

int rechercherClient(liste_client l, unsigned int id);

void afficher_liste(liste_client l);

#endif
