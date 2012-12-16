#ifndef H_TRAIT_SRV
#define H_TRAIT_SRV

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*
  auteur : Lloret
	but : fonction récursive de parcours d'arborescence prend en paramètre un chemin d'arbo sur un dossier (avec droits en lecture)
	paramètres : nom du chemin du dossier et fichier dans lequel enregistrer
	renvoi : //

*/

void parcoursServeur(char *nom, FILE* fichier); 


/*
	auteur : Lloret
	but : enregistre toutes les infos du repertoire dans un fichier texte
	paramètres : nom du chemin du repertoire
	renvoi : //

*/

void enregistrerBaseServeur(char *nom);


/*
	auteur : Lloret
	but : rechercher si un objet est présent dans la base serveur
	paramètres : nom du chemin de l'objet recherché
	renvoi : 0 si oui ; 1 si non

*/

int rechercherNomDansBaseClient(char nom[50]);


/*
	auteur : Lloret
	but : comparer les deux dates
	paramètres : tous les para nécessaires pour comparer une date1 à une date2
	renvoi : 0 si date1 > date2 ; 1 si date2 > date1 ; 2 si date1 = date2

*/
int ComparerDatesServeur(char DateMois1[50], int DateJour1, char DateHeure1[50], int DateAnnee1,char DateMois2[50], int DateJour2, char DateHeure2[50], int DateAnnee2);


/*
	auteur : Lloret
	but : compare la base serveur avec la base client et en ressort les modifications à faire
	paramètres : 
	renvoi :
*/

void comparerBasesDepuisServeur();


#endif
