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
    char *user;
} s_info;

typedef struct s_message {
    char *type;
    char *status;
    int sessionid;
    char *user;
    s_info info;
} message;

void initialisationStructureMessage(message *mess);
int toString(message *mess, unsigned char **chaine);
message decodeMessage(char message[1024]);

#endif
