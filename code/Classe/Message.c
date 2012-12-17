
// Ne marche pas pour l'instant, erreur de segmentation au niveau des appels de fonctions
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Message.h"
#include "asprintf.h"


void initialisationStructureMessage(message *mess)
{
    mess->type = NULL;
    mess->status = NULL;
    mess->sessionid = -1;
    mess->user = NULL;
    mess->info.number = -1;
    mess->info.id = -1;
    mess->info.size = -1;
    mess->info.name = NULL;
    mess->info.sha1 = -1;
    mess->info.date = NULL;
    mess->info.path = NULL;
    mess->info.user = NULL;
}

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
	auteur : GAUTIER Philippe
	but : mettre une structure message sous forme de String
	paramètres : message
	renvoi : string en paramètre (chaine)

*/

int toString(message *mess, unsigned char **chaine)
{
    // document pointer
    xmlDocPtr doc = NULL;
    xmlNodePtr root_node = NULL, node_info = NULL;//user = NULL, type = NULL, status = NULL, info = NULL;/* node pointers */
    int *taille = NULL;

    printf("user: %s", mess->user);

    if( (mess->user != NULL) || (mess->sessionid != -1) || (mess->type != NULL) || (mess->status != NULL) ){
        // création d'un nouveau document
        doc = xmlNewDoc(BAD_CAST "1.0");
        root_node = xmlNewNode(NULL, BAD_CAST "message");
        xmlDocSetRootElement(doc, root_node);

        // test de l'existence des variables user, type, status, ... dans la structure et ajout de la node

        if(mess->user != NULL){

            xmlNewChild(root_node, NULL, BAD_CAST "user", BAD_CAST mess->user);
        }

        if(mess->sessionid != -1){

            xmlNewChild(root_node, NULL, BAD_CAST "sessionid", xmlXPathCastNumberToString(mess->sessionid));
        }

        if(mess->type != NULL){


            xmlNewChild(root_node, NULL, BAD_CAST "type", BAD_CAST mess->type);
        }

        if(mess->status != NULL){

            xmlNewChild(root_node, NULL, BAD_CAST "status", BAD_CAST mess->status);
        }

        if( (mess->info.number != -1) || (mess->info.id != -1) || (mess->info.size != -1) || (mess->info.name != NULL) || (mess->info.sha1 != -1) || (mess->info.date != NULL) || (mess->info.path != NULL) || (mess->info.user != NULL)) {

            node_info = xmlNewNode(NULL, BAD_CAST "info");
            xmlAddChild	(root_node, node_info);

            if(mess->info.number != -1){

                xmlNewChild(node_info, NULL, BAD_CAST "number", xmlXPathCastNumberToString(mess->info.number));
            }

            if(mess->info.id != -1){

                xmlNewChild(node_info, NULL, BAD_CAST "id", xmlXPathCastNumberToString(mess->info.id ));
            }

            if(mess->info.size != -1){

                xmlNewChild(node_info, NULL, BAD_CAST "size", xmlXPathCastNumberToString(mess->info.size));
            }

            if(mess->info.sha1 != -1){

                xmlNewChild(node_info, NULL, BAD_CAST "sha1", xmlXPathCastNumberToString(mess->info.sha1));
            }

            if(mess->info.name != NULL){

                xmlNewChild(node_info, NULL, BAD_CAST "name", BAD_CAST mess->info.name);
            }

            if(mess->info.date != NULL){

                xmlNewChild(node_info, NULL, BAD_CAST "date", BAD_CAST mess->info.date);
            }

            if(mess->info.path != NULL){

                xmlNewChild(node_info, NULL, BAD_CAST "path", BAD_CAST mess->info.path);
            }

            if(mess->info.user != NULL){

                xmlNewChild(node_info, NULL, BAD_CAST "user", BAD_CAST mess->info.user);
            }
        }
    }

    // enegistrement dans une chaine de caractère
    xmlDocDumpMemory(doc, chaine,taille);

    // libération mémoire

    xmlFreeDoc(doc);
    xmlCleanupParser();

    return 0;
}

/*
	auteur : Lloret
	but : trouver l'id User dans le message
	paramètres : message
	renvoi : string en paramètre (user)

*/


