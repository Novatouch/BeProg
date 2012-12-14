#define POSIX_C_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
//, essayer de faire l'enregistrement sous formes de structure Directory avec (nom,nbOctet,Date)

void parcours(char *nom, FILE* fichier) // fonction récursive de parcours d'arborescence prend en paramètre un chemin d'arbo sur un dossier (avec droits en lecture)
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
      printf("%-30s %30d octets %s\n",next,(int)pinfos.st_size,ctime(&pinfos.st_mtime));
    fprintf(fichier, "%-30s %30d octets %s\n",next,(int)pinfos.st_size,ctime(&pinfos.st_mtime)); // enrg fichiers
      cpt+=(int)pinfos.st_size;
    }
    if(S_ISDIR(pinfos.st_mode)&&strcmp(fich->d_name,".")&&strcmp(fich->d_name,"..")) // sur les dossiers
    {
      parcours(next, fichier);
    }
  }
  printf("Total %-30s %30d octets %s\n",nom,cpt,ctime(&pinfos.st_mtime));
  fprintf(fichier, "Total %-30s %30d octets %s\n",nom,cpt,ctime(&pinfos.st_mtime)); // enrg dossiers
  closedir(rep);
  
}

int main(int argc, char *argv[]) // main de test à transformer en fonction EnregistrerArbo
{
  /*if(argc!=2)
  {
    fprintf(stderr,"Usage: %s rep\n",argv[0]);
    exit(1);
  }
  parcours(argv[1]);*/
  FILE* fichier = NULL; // Fichier pour enregistrer l'arborescence

  fichier = fopen("base.txt", "w+"); // Enregistrer l'arborescence dans le fichier base.txt
  parcours("/home/quighi/Documents/Test", fichier);
  fclose(fichier);
  return 0;
}