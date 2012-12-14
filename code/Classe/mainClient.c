#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

//#include "Classe/Client.h"
//#include "Classe/ConnexionClient.h"
//#include "Classe/TraitementClient.h"

int main()
{

	pid_t pid;

	pid = fork();

	if (pid == -1) {

		/* erreur - impossible de créer un fils */

		perror("fork error");

		exit(1);

	}
	else if (pid == 0) {

		//code du fils
		printf("processus FILS >>>> fork\n");
	}
	else{

		//code du père
		printf("processus PERE >>>> fork\n");
	}
		
	return 0;
}
