
// Ne marche pas pour l'instant, erreur de segmentation au niveau des appels de fonctions
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Message.h"
#include "asprintf.h"

/*
	auteur : GAUTIER Philippe
	but : intitialisation de la structure. Permet de savoir si les variables sont vides ou si elles contiennent des variables.
	paramètres : structure message
	renvoi : string en paramètre (chaine)

*/

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

int toString(message *mess, char **chaine)
{
    // pointeur de node xml
    xmlDocPtr doc = NULL;
    xmlNodePtr root_node = NULL, node_info = NULL;
    int *taille = NULL;
    xmlChar *ch;


    //teste l'existence d'au mons une de ces variables
    if( (mess->user != NULL) || (mess->sessionid != -1) || (mess->type != NULL) || (mess->status != NULL) ){
        // création d'un nouveau document
        doc = xmlNewDoc(BAD_CAST "1.0");
        root_node = xmlNewNode(NULL, BAD_CAST "message");
        xmlDocSetRootElement(doc, root_node);

        // test de l'existence des variables user, type, status, ... dans la structure et ajout de la node si elle existe

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

        // même principe que plus haut
        if( (mess->info.number != -1) || (mess->info.id != -1) || (mess->info.size != -1) || (mess->info.name != NULL) || (mess->info.sha1 != -1) || (mess->info.date != NULL) || (mess->info.path != NULL) ) {

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
        }
    }

    // enegistrement dans une chaine de caractère
    xmlDocDumpMemory(doc, &ch,taille);

    asprintf(chaine, "%s", ch);
    // libération mémoire

    xmlUnlinkNode(root_node);
    xmlFreeNode(root_node);
    xmlFreeDoc(doc);
    xmlCleanupParser();

    return 0;
}

/*
	auteur : Gautier
	but : Fonction permettant de faire une recherche sur une chaine dans un arbre XML DOM
	paramètres : pointeur sur int, chaine de recherche, context de recherche Xpath
	renvoi : 0 ok 1 NOK

*/


int rechercherChaine(char **chaine, char *recherche, xmlXPathContextPtr *ctxt)
{
    xmlXPathObjectPtr xpathRes;
    xmlNodePtr node_recherche;

    xpathRes = xmlXPathEvalExpression(BAD_CAST recherche, *ctxt);
    if( xpathRes == NULL){
        return 1;
    }
    // si la requête Xpath a bien retournée des nodes
    if (xpathRes->type != XPATH_NODESET){

        return 1;
    }
    // vérifie que plus d'une seule node à été trouvée
    if(xpathRes->nodesetval->nodeNr != 1){
        return 0;
    }

    // recuperation de la valeur
    node_recherche = xpathRes->nodesetval->nodeTab[0];

    // recuperation de la chaine
    asprintf(chaine, "%s", xmlXPathCastNodeToString(node_recherche) );

    return 0;
}

/*
	auteur : Gautier
	but : Fonction permettant de faire une recherche sur un nombre dans un arbre XML DOM
	paramètres : pointeur sur int, chaine de recherche, context de recherche Xpath
	renvoi : 0 ok 1 NOK

*/

int rechercherNombre(int *nombre, char *recherche, xmlXPathContextPtr *ctxt)
{
    xmlXPathObjectPtr xpathRes;
    xmlNodePtr node_recherche;

    xpathRes = xmlXPathEvalExpression(BAD_CAST recherche, *ctxt);
    if(xpathRes == NULL){
        return 1;
    }
    // si la requête Xpath a bien retournée des nodes
    if(xpathRes->type != XPATH_NODESET){
        return 1;
    }
    // vérifie que plus d'une seule node à été trouvée
    if(xpathRes->nodesetval->nodeNr != 1){

        return 0;
    }


    // recuperation de la valeur
    node_recherche = xpathRes->nodesetval->nodeTab[0];

    // recuperation de la chaine
    *nombre = (int) (xmlXPathCastStringToNumber(xmlXPathCastNodeToString(node_recherche)));

    return 0;
}


/*
	auteur : Lloret et Gautier
	but : trouver l'id User dans le message
	paramètres : message
	renvoi : string en paramètre (user)

*/

int decodeMessage(char *chaine, message *message)
{

    xmlDocPtr doc;
    xmlNodePtr root_node;

    // contexte Xpath
    xmlXPathContextPtr ctxt;



    // créer un arbre DOM à partir de la chaine
    doc = xmlParseMemory(chaine, strlen(chaine));

    if (doc == NULL) {
        fprintf(stderr, "requete XML invalide\n");
        return 1;
    }
    // Récupération de la racine
    root_node = xmlDocGetRootElement(doc);

    if (root_node == NULL) {
        fprintf(stderr, "Document XML vierge\n");
        xmlFreeDoc(doc);
        return 1;
    }

    // initialisation Xpath
    xmlXPathInit();
    ctxt = xmlXPathNewContext(doc);

    if ( ctxt == NULL){
        // initialisation complète
        fprintf(stderr, "Problème contexte Xpath\n");
        return 1;
    }


    if( (rechercherChaine(&message->user, "/message/user", &ctxt)) != 0){
        return 1;
    }

    if( (rechercherChaine(&message->status, "/message/status", &ctxt)) != 0){
        return 1;
    }

    if( (rechercherChaine(&message->type, "/message/type", &ctxt)) != 0){
        return 1;
    }


    if( (rechercherNombre(&message->sessionid, "/message/sessionid", &ctxt)) != 0){
        return 1;
    }

    if( (rechercherNombre(&message->info.number, "/message/info/number", &ctxt)) != 0){
        return 1;
    }

    if( (rechercherNombre(&message->info.id, "/message/info/id", &ctxt)) != 0){
        return 1;
    }

    if( (rechercherNombre(&message->info.size, "/message/info/size", &ctxt)) != 0){
        return 1;
    }

    if( (rechercherNombre(&message->info.sha1, "/message/info/sha1", &ctxt)) != 0){
        return 1;
    }

    if( (rechercherChaine(&message->info.name, "/message/info/name", &ctxt)) != 0){
        return 1;
    }

    if( (rechercherChaine(&message->info.date, "/message/info/date", &ctxt)) != 0){
        return 1;
    }

    if( (rechercherChaine(&message->info.path, "/message/info/path", &ctxt)) != 0){
        return 1;
    }

    // récupération des valeur des différents champs d'un message

    // libération mémoire
    xmlUnlinkNode(root_node);
    xmlFreeNode(root_node);
    xmlFreeDoc(doc);
    xmlCleanupParser();

    return 0;
}


