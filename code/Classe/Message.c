
// Ne marche pas pour l'instant, erreur de segmentation au niveau des appels de fonctions
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "message.h"

struct s_info {
char *number;
char *id;
char *size;
char *name;
char *sha1;
char *date;
char *path;
char *user;
};

struct s_message {
char *type;
char *status;
char *sessionid;
char *user;
};

/* Message de la forme :
  <message> 
	<user>identidiant utilisateur</user> 
	<sessionid>identifiant de la session</sessionid> 
	<type>type de la requete</type> 
	<status>status de la requête</status> 
	<info> 
		Les champs varieront en fonction de la nature de la requête 
	</info> 
  </message> 
*/
  
  
/*
	auteur : Lloret
	but : mettre une structure message sous forme de String
	paramètres : message
	renvoi : string en paramètre (chaine)

*/

void toString(message mess, char chaine[1024])
{
  
  strcpy(chaine, "<message> <user>");
  strcat(chaine, mess.user);/*On ajoute le champs user à la chaîne grâce à la fonction strcat*/
  strcat(chaine, "</user> <sessionid>"); /*on sépare les champs par un espace*/
  strcat(chaine, mess.sessionid);
  strcat(chaine, "</sessionid> <type>");
  strcat(chaine, mess.type);
  strcat(chaine, "</type> <status>");
  strcat(chaine, mess.status);
  strcat(chaine, "</status> </message>");
  
  //printf("%s\n", chaine);
  
}

/*
	auteur : Lloret
	but : trouver l'id User dans le message
	paramètres : message
	renvoi : string en paramètre (user)

*/

void determinerUser(char message[1024], char user[20]) {
  

  int i = 0;
  int j = 0;
  int k = 0;
  int l = 0;


  for(j = 0 ; message[j] = ' ' ; j++) { // on atteint le premier espace
	for (i=j ; message[i] = '>'; i++) { // on atteint le > de <user>
	    for(k=i+1 ; message[k] != '<' ; k++) { //on va jusqu'au < de </user>
		user[l] = message[k];
		l++;
	    }
	}
  }
  
}

/*
	auteur : Lloret
	but : trouver l'id Session dans le message
	paramètres : message
	renvoi : string en paramètre (sessionid)

*/

void determinerSessionid(char message[1024], char sessionid[20]) {
  
  int i = 0;
  int j = 0;
  int k = 0;
  int l = 0;
  int a = 0;


  for(j = 0 ; message[j] != ' ' ; j++) { // on atteint le premier espace
	for (i=j+1 ; message[i] = ' '; i++) { // on atteint le 2e espace
	    for(k=i ; message[k] = '>' ; k++) { //on atteint le > de <sessionid>
		for(a=k+1 ; message[a] != '<' ; a++) { //on va jusqu'au < de </sessionid>
		  sessionid[l] = message[a];
		  l++;
		}
	    }
	}
  }
  
} 
  
/*
	auteur : Lloret
	but : trouver le type dans le message
	paramètres : message
	renvoi : string en paramètre (type)

*/

void determinerType(char message[1024], char type[20]) {
 
  int i = 0;
  int j = 0;
  int k = 0;
  int l = 0;
  int a = 0;
  int b = 0;


  for(j = 0 ; message[j] != ' ' ; j++) { // on atteint le premier espace
	for (i=j+1 ; message[i] = ' '; i++) { // on atteint le 2e espace
	    for(k=i+1 ; message[k] = ' ' ; k++) { //on atteint le 3e espace
		for(a=k ; message[a] = '>' ; a++) { //on atteint le > de <type>
		    for(b=a+1; message[b] != '<'; b++) { //on va jusqu'au < de </type>
			type[l] = message[b];
			l++;
		    }
		}
	    }
	}
  }
  
  
}

/*
	auteur : Lloret
	but : trouver le status dans le message
	paramètres : message
	renvoi : string en paramètre (status)

*/

void determinerStatus(char message[1024], char status[20]) {
  
  int i = 0;
  int j = 0;
  int k = 0;
  int l = 0;
  int a = 0;
  int b = 0;
  int c = 0;


  for(j = 0 ; message[j] != ' ' ; j++) { // on atteint le premier espace
	for (i=j+1 ; message[i] = ' '; i++) { // on atteint le 2e espace
	    for(k=i+1 ; message[k] = ' ' ; k++) { //on atteint le 3e espace
		for(a=k+1 ; message[a] = ' ' ; a++) { //on atteint le 4e espace
		    for(b=a; message[b] = '>'; b++) { //on atteint le > de <status>
			for(c=b+1 ; message[c] != '<'; c++) { //on va jusqu'au < de </status>
			    status[l] = message[c];
			    l++;
			}
		    }
		}
	    }
	}
  }
  
  
  
}

/*
	auteur : Lloret
	but : mettre un String sous forme de structure message
	paramètres : message
	renvoi : string

*/

message decodeMessage(char message[1024])
{
  struct s_message mess;
  char type[20] = "";
  char status[20] = "";
  char sessionid[20] = "";
  char user[20] = "";
  printf("razaztaat");
  
  determinerUser(message,user);/*
  strcpy(mess.user,user);
  
  determinerSessionid(message,sessionid);
  strcpy(mess.sessionid,sessionid);
  
  determinerType(message,type);
  strcpy(mess.type,type);
  
  determinerStatus(message,status);
  strcpy(mess.status,status);*/

  
  return(mess);
  
}
/*
int main(void) {
  
  message m;
  char chaine[1024];
  char user[10];

  m.user = "user";
  m.sessionid = "sessionid";
  m.status = "status";
  m.type = "type";
  
  toString(m,chaine);
  printf("%s\n\n",chaine);
  
  decodeMessage(chaine);

  
  return(0);
}

*/
