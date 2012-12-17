#define POSIX_C_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

#include "TraitementServeur.h"

/*
  auteur : Lloret
	but : fonction récursive de parcours d'arborescence prend en paramètre un chemin d'arbo sur un dossier (avec droits en lecture)
	paramètres : nom du chemin du dossier et fichier dans lequel enregistrer
	renvoi : //

*/

void parcoursServeur(char *nom, FILE* fichier) 
{
  int cpt=0;
  char next[2000];
  struct dirent *fich;
  struct stat pinfos;
  DIR *rep;
  rep=opendir(nom);
  
  
  if(rep==NULL)
  {
    perror(nom);
    exit(2);
  }
  while((fich=readdir(rep))!=NULL)
  {
    sprintf(next,"%s/%s",nom,fich->d_name);
    if(stat(next,&pinfos)==-1)
    {
      perror("Stat fich->d_name");
      exit(3);
    }
    if(S_ISREG(pinfos.st_mode)) // sur les fichiers
    {
      printf("%s %d %s\n",next,(int)pinfos.st_size,ctime(&pinfos.st_mtime));
    fprintf(fichier, "%s %d %s\n",next,(int)pinfos.st_size,ctime(&pinfos.st_mtime)); // enrg fichiers
      cpt+=(int)pinfos.st_size;
    }
    if(S_ISDIR(pinfos.st_mode)&&strcmp(fich->d_name,".")&&strcmp(fich->d_name,"..")) // sur les dossiers
    {
      parcoursServeur(next, fichier);
    }
  }
  printf("%s %d %s\n",nom,cpt,ctime(&pinfos.st_mtime));
  fprintf(fichier, "%s %d %s\n",nom,cpt,ctime(&pinfos.st_mtime)); // enrg dossiers
  closedir(rep);
  
}

/*
	auteur : Lloret
	but : enregistre toutes les infos du repertoire dans un fichier texte
	paramètres : nom du chemin du repertoire
	renvoi : //

*/

void enregistrerBaseServeur(char *nom)
{

  FILE* fichier = NULL; // Fichier pour enregistrer l'arborescence
  remove(nom);
  fichier = fopen("baseServeur.txt", "w+"); // Enregistrer l'arborescence dans le fichier base.txt
  parcoursServeur(nom, fichier);
  fclose(fichier);

}

/*
	auteur : Lloret
	but : recupère les infos de la base
	paramètres :
	renvoi : //

*/

void recupererinfosbaseServeur() {
  
  char nomChemin[50] = "";
  char DateJourS[50] = "";
  char DateMois[50] = "";
  int DateJour = 0;
  char DateHeure[50] = "";
  int DateAnnee = 0;
  int nombre = 0;
  FILE* fichier = NULL;
  fichier = fopen("baseServeur.txt", "r");
  
  /* Le fichier possède les informations sous la forme : "$nomChemin $nombre $Date\n"
   */
  
  fscanf(fichier, "%s %d %s %s %d %s %d", nomChemin, &nombre, DateJourS, DateMois, &DateJour, DateHeure, &DateAnnee);
  printf("La ligne trouvée est : %s %d %s %s %d %s %d",  nomChemin, nombre, DateJourS, DateMois, DateJour, DateHeure, DateAnnee);
 
  
  fclose(fichier);
}

/*
	auteur : Lloret
	but : rechercher si un objet est présent dans la base serveur
	paramètres : nom
	renvoi : 0 si oui ; 1 si non

*/

int rechercherNomDansBaseClient(char nom[50]) {
  
  int trouve = 1;
  char nomChemin[50] = "";
  char DateJourS[50] = "";
  char DateMois[50] = "";
  int DateJour = 0;
  char DateHeure[50] = "";
  int DateAnnee = 0;
  int nombre = 0;
  FILE* fichier = NULL;
  fichier = fopen("baseClient.txt", "r");
  while(fgetc(fichier)!=EOF) { //tant qu'on est pas à la fin du fichier
      fscanf(fichier, "%s %d %s %s %d %s %d", nomChemin, &nombre, DateJourS, DateMois, &DateJour, DateHeure, &DateAnnee);
      printf("La ligne rechercherNomDansBaseClient trouvée est : %s %d %s %s %d %s %d\n",  nomChemin, nombre, DateJourS, DateMois, DateJour, DateHeure, DateAnnee);
      if(strcmp(nom, nomChemin) == 0) {
	printf("Le nom du fichier est présent dans la base Client\n");
	trouve = 0;
	break;
      }
  }
  fclose(fichier);
  return trouve;
}

/*
	auteur : Lloret
	but : comparer deux heures
	paramètres : heure1 et heure2
	renvoi : 0 si heure1 > heure2 ; 1 si heure2 > heure1 ; 2 si heure2 = heure1

*/

int comparerHeures(char heure1[50], char heure2[50]) {
  
  // heure de la forme : 19:01:05
  int valeur = 0;
  int h1 = 0;
  int h2 = 0;
  
  h1 = (heure1[0] * 60 * 60 * 10) + (heure1[1] * 60 * 60) + (heure1[3] * 60 * 10) + (heure1[4] * 60) + (heure1[6] * 10) + heure1[7];
  h2 = (heure2[0] * 60 * 60 * 10) + (heure2[1] * 60 * 60) + (heure2[3] * 60 * 10) + (heure2[4] * 60) + (heure2[6] * 10) + heure2[7];
  
  if(h1 > h2) {
    return 0;
  }
  
  else if(h2 > h1) {
    return 1;
  }
  
  else { //h2 = h1
    printf("heures identiques : erreur\n");
    return 2;
  }
  
}
/*
	auteur : Lloret
	but : mettre en mois de string en int
	paramètres : mois en string
	renvoi : mois en int ou 0 si erreur

*/
int MoisEnNombre(char mois[50]) {
  
  if(mois[0] == 'J') {
    
      if(mois[1] == 'a') {
	return 1;
      }
    
      else if(mois[1] == 'u') {
      
	  if(mois[2] == 'n') {
	    return 6;
	  }
      
	  else if(mois[2] == 'l') {
	    return 7;
	  }
	  
	  else return 0;
      }
      
      else return 0;
      
      
  }
  
  else if(mois[0] == 'F') {
      return 2;
  }
  
  else if(mois[0] == 'M') {
    
      if(mois[1] == 'a') {
	  
	  if(mois[2] == 'r') {
	    return 3; 
	  }
	  
	  else if(mois[2] == 'y') {
	    return 5;
	  }
	  
	  else return 0;
      }
      
      else return 0;
      
  }
  
  else if(mois[0] == 'A') {
      
      if(mois[1] == 'p') {
	  return 4;
      }
  
      else if(mois[1] == 'u') {
	return 8;
      }
      
      else return 0;
      
  }
	
  else if(mois[0] == 'S') {
      return 9;  
  }
  
  else if(mois[0] == 'O') {
      return 10;
  }
  
  else if(mois[0] == 'N') {
      return 11;
  }
  
  else if(mois[0] == 'D') {
    return 12;
  }
  
  else return 0;
	
}

/*
	auteur : Lloret
	but : comparer deux mois 
	paramètres : mois1 et mois2
	renvoi : 0 si mois1 > mois2 ; 1 si mois2 > mois1 ; 2 si mois2 = mois1

*/


int comparerMois(char DateMois1[50], char DateMois2[50]) {
  
  // mois sous la forme d'une chaîne de caractère Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
  
  if(MoisEnNombre(DateMois1) == MoisEnNombre(DateMois2)) {
    return 2;
  }
  
  else if(MoisEnNombre(DateMois1) > MoisEnNombre(DateMois2)) {
    return 0;
  }
  
  else return 1;
  
  
}

/*
	auteur : Lloret
	but : comparer les deux dates
	paramètres : tous les para nécessaires pour comparer une date1 à une date2
	renvoi : 0 si date1 > date2 ; 1 si date2 > date1 ; 2 si date1 = date2

*/
int ComparerDatesServeur(char DateMois1[50], int DateJour1, char DateHeure1[50], int DateAnnee1,char DateMois2[50], int DateJour2, char DateHeure2[50], int DateAnnee2) {

  if(DateAnnee1 == DateAnnee2) {
    
      if(comparerMois(DateMois1,DateMois2) == 2) { //DateMois1 == DateMois2

	  if(DateJour1 == DateJour2) {
	
	      if(comparerHeures(DateHeure1, DateHeure2) == 0) {
		  return 0;
	      }
	
	      else {
		  return 1;
	      }
	
	  }
      
	  else if(DateJour1 > DateJour2) {
	     return 0;
	  }
      
	  else {
	     return 1;
	  }//comparaisonJours
      }
      
      else if (comparerMois(DateMois1,DateMois2) == 0) {
	return 0;
      }
      
      else {
	return 1;
      }//comparaisonMois
  }
  
  else if(DateAnnee1 > DateAnnee2) {
    return 0;
  }
  
  else {
    return 1;
  }
      

}

/*
	auteur : Lloret
	but : compare la base serveur avec la base client et en ressort les modifications à faire
	paramètres : 
	renvoi :
*/

void comparerBasesDepuisServeur() {
  /* on a deux fichiers texte : Base Client et Base Serveur et on veut les comparer
   * On va recuperer une ligne dans la base Serveur, regarder quel est le nom de cet objet, rechercher cet objet dans la base Client puis comparer les dates
   * 
  */
  char nomChemin[50] = "";
  char DateJourS[50] = "";
  char DateMois[50] = "";
  int DateJour = 0;
  char DateHeure[50] = "";
  int DateAnnee = 0;
  int nombre = 0;
  
  char nomChemin1[50] = "";
  char DateJourS1[50] = "";
  char DateMois1[50] = "";
  int DateJour1 = 0;
  char DateHeure1[50] = "";
  int DateAnnee1 = 0;
  int nombre1 = 0;
  

  FILE* fichier = NULL;
  fichier = fopen("baseServeur.txt", "r");
  FILE* fichier1 = NULL;
  fichier1 = fopen("baseClient.txt", "r");
  
  while(fgetc(fichier)!=EOF) { //tant qu'on est pas à la fin du fichier baseServeur
      fscanf(fichier, "%s %d %s %s %d %s %d", nomChemin, &nombre, DateJourS, DateMois, &DateJour, DateHeure, &DateAnnee);
      printf("La ligne serveur trouvée est : %s %d %s %s %d %s %d\n",  nomChemin, nombre, DateJourS, DateMois, DateJour, DateHeure, DateAnnee);
      
      if (rechercherNomDansBaseClient(nomChemin) == 0) { //
		  while(fgetc(fichier1)!=EOF) { //tant qu'on est pas à la fin du fichier baseClient
		            fscanf(fichier1, "%s %d %s %s %d %s %d", nomChemin1, &nombre1, DateJourS1, DateMois1, &DateJour1, DateHeure1, &DateAnnee1);
			    printf("La ligne client trouvée est : %s %d %s %s %d %s %d\n",  nomChemin1, nombre1, DateJourS1, DateMois1, DateJour1, DateHeure1, DateAnnee1);
		
			    if(strcmp(nomChemin, nomChemin1) == 0) { // on a le bon nom de fichier
		
				// il faut maintenant comparer les dates pour voir si le fichier a été mis à jour
				if((strcmp(DateJourS, DateJourS1) == 0) && (strcmp(DateMois, DateMois1) == 0) && (DateJour == DateJour1) && (strcmp(DateHeure, DateHeure1) == 0) && (DateAnnee == DateAnnee1)) {
				  // les deux objets sont bien les même --> pas de modif
				  printf("\n Objet correspondant dans la base Client : RAS\n\n\n");
				  break;
				  
				}
				// comparer si la date de maj est supérieure dans le client par rapport au serveur
				else if(ComparerDatesServeur(DateMois, DateJour, DateHeure, DateAnnee, DateMois1, DateJour1, DateHeure1, DateAnnee1) == 0) {
				  // la comparaison des dates montre que la date niveau Serveur est > à la date Niveau Client
				  // la dernière maj de l'obj est donc au niveau du serveur  --> donc on doit faire cette maj au niveau client
				   printf("L'objet : %s doit être téléchargé par le client pour une maj\n\n\n", nomChemin);
				   
				   break;
				}
				  
				else {
				  // la dernière maj de l'obj est au niveau du client
				  printf("L'objet : %s doit être téléchargé par le serveur pour une maj\n\n\n", nomChemin);
				  
				  break;
				}
		
			  
			    }
		   
		  }
      }
      
      else { // on n'a pas trouvé l'objet dans la base client donc il n'y est pas présent --> Supprimer celui-ci
	printf("L'objet : %s doit être supprimé par le serveur\n\n\n", nomChemin);
	
      }
  }
  fclose(fichier);
  fclose(fichier1);
  
}
int main(void) {

char *nom = "/home/melvin/PJ/base";
char nomObj[50] = "/home/melvin/PJ/base/Sousrep";
int i = 0;

comparerBasesDepuisServeur();


return 0;  
}
