#ifndef H_MESSAGE
#define H_MESSAGE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>



typedef struct s_info {
    int number;
    int id;
    int size;
    char *name;
    int sha1;
    char *date;
    char *path;
} s_info;

typedef struct s_message {
    char *type;
    char *status;
    int sessionid;
    char *user;
    s_info info;
} message;



void initialisationStructureMessage(message *mess);
int toString(message *mess, char **chaine);
int rechercherNombre(int *nombre, char *recherche, xmlXPathContextPtr *ctxt);
int rechercherChaine(char **chaine, char *recherche, xmlXPathContextPtr *ctxt);
int decodeMessage( char *chaine, message *message);


#endif
