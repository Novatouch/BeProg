#ifndef H_MESSAGE
#define H_MESSAGE

struct info {
	char *number;
	char *id;
	char *size;
	char *name;
	char *sha1;
	char *date;
	char *path;
	char *user;
} info;

struct message {
	char *type;
	char *status;
	char *sessionid;
	char *user;
} message;

char * toString(message mess);
message decodeMessage(char *message);

#endif
