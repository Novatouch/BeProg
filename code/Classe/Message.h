#ifndef H_MESSAGE
#define H_MESSAGE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct s_info info;
typedef struct s_message message;

void toString(message mess, char chaine[1024]);
message decodeMessage(char message[1024]);

#endif