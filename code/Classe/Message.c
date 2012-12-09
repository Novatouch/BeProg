

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "message.h"

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
	renvoi : string

*/

char * toString(message mess)
{

  char * chaine = "";
  
  strcpy(chaine, "<message> <user>");
  strcat(chaine, message.user);/*On ajoute le champs user à la chaîne grâce à la fonction strcat*/
  strcat(chaine, "</user> <sessionid>"); /*on sépare les champs par un espace*/
  strcat(chaine, message.sessionid);
  strcat(chaine, "</sessionid> <type>");
  strcat(chaine, message.type);
  strcat(chaine, "</type> <status>");
  strcat(chaine, message.status);
  strcat(chaine, "</status> </message>");
  
  printf("%s\n", chaine);
  
  return(chaine);
  
}

/*
	auteur : Lloret
	but : mettre un String sous forme de structure message
	paramètres : message
	renvoi : string

*/

message decodeMessage(char *message)
{
  message mess;
  mess.type = determinerType(message);
  mess.status = determinerStatus(message);
  mess.sessionid = determinerUser(message);
  mess.user = determinerSessionid(message);
  
  return(mess);
  
}

char * determinerUser(char *message) {
  
  
  
}

char * determinerSessionid(char *message) {
  
  
  
}
char * determinerType(char *message) {
  
  
  
}

char * determinerStatus(char *message) {
  
  
  
  
}
