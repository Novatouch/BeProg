#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ListeClient.h"



typedef struct s_case_liste_client {

  unsigned int idClient;
  unsigned int idSession;
  struct s_case_liste_client *suiv;
  struct s_case_liste_client *prec;

} case_liste_client;

struct liste
{
    struct s_case_liste_client *tete;
    struct s_case_liste_client *queue;

};


/*
	auteur : Lloret
	but : initialiser la liste
	paramètres : //
	renvoi : liste

*/

liste_client initilisation() {
  liste_client l;
  l = (liste_client)malloc(sizeof(struct liste));
  if(l == NULL) {
    printf("Erreur d'initilisation\n");
  }
  l->tete = NULL;
  l->queue = NULL;

  return l;
}

/*
	auteur : Lloret
	but : vérifie si la liste est vide
	paramètres : liste
	renvoi : bool

*/

bool listeVide(liste_client l) {

  return(l->tete == NULL);

}

/*
	auteur : Lloret
	but : ajouter un client à la liste
	paramètres : la liste et l'id du client
	renvoi : 0 si ajouté sinon 1

*/


int ajouterClient(liste_client l, unsigned int id)
{
  case_liste_client *p;
  p = (case_liste_client *)malloc(sizeof(struct s_case_liste_client));

  if(p == NULL) {
    printf("Erreur d'ajout\n");
    return(1);
  }

  p->idClient = id;

  if(listeVide(l)) {
    l->tete = p;
    l->queue = p;
    p->prec = NULL;
    p->suiv = NULL;
  }

  else {
    p->suiv = NULL;
    p->prec = l->queue;
    l->queue->suiv = p;
    l->queue = p;
  }

  return(0);
}

/*
	auteur : Lloret
	but : supprimer un client dans la liste
	paramètres : liste et id du client à supprimer
	renvoi : 0 si supprimé 1 sinon

*/


int supprimerClient(liste_client l, unsigned int id)
{

  case_liste_client *sup,*current;

  if(listeVide(l)) {
    printf("Erreur : liste vide\n");
    return(1);
  }

  if(l->tete->idClient == id) { // supprimer la tête
    sup = l->tete;
    l->tete = l->tete->suiv;
    l->tete->prec = NULL;
  }

  else if(l->queue->idClient == id) { // supprimer la queue
    sup = l->queue;
    l->queue->prec->suiv = NULL;
    l->queue = l->queue->prec;
  }

  else { //supprimer dans la liste
    current = l->tete;
    while(current->idClient != id) {

      if(current->suiv == NULL) {
	printf("Client non trouvé\n");
	return(1);
      }
      current = current->suiv;

    }

    // on a trouvé celui qu'on veut supprimer
    sup = current;
    current->prec->suiv = current->suiv;
    current->suiv->prec = current->prec;
  }

  free(sup);
  return(0);
}

/*
	auteur : Lloret
	but : rechercher si un client est dans liste
	paramètres : liste et id du client recherché
	renvoi : 0 si trouvé 1 sinon

*/

int rechercherClient(liste_client l, unsigned int id)
{
  case_liste_client *current;

  if(listeVide(l)) {
    printf("Erreur : liste vide\n");
    return(1);
  }

  if(l->tete->idClient == id) {
    printf("Le Client est la tête\n");
    return(0);
  }

  else if(l->queue->idClient == id) {
    printf("Le Client est la queue\n");
    return(0);
  }

  else {
    current = l->tete;

    while(current->idClient != id) {

      if(current->suiv == NULL) {
	printf("Client non trouvé\n");
	return(1);
      }
      current = current->suiv;

    }

    printf("Le Client est le corps\n");
    return(0);

  }

}

/*
	auteur : Lloret
	but : affiche la liste
	paramètres : liste
	renvoi : //

*/

void afficher_liste(liste_client l) {

  if(listeVide(l)) {
    printf("La liste est vide\n");
  }
  else {
    case_liste_client *p = l->tete;

    while(p != NULL) {
      printf(" %d ", p->idClient);
      p = p->suiv;
    }
  }
}

/* MAIN test

int main(void) {

  int i;
  liste_client x = initilisation();


  ajouterClient(x,2);
  ajouterClient(x,4);
  ajouterClient(x,7);
  ajouterClient(x,1);
  supprimerClient(x,1);
  afficher_liste(x);


  i = rechercherClient(x,4);



  return(0);

}

*/
