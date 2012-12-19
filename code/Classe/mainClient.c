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
	config_connex connex_permanente, connex_temporaire;
	config_client configClient;
	pid = fork();
	
	initialiserConnexion(&connex_permanente);
	initialiserConnexion(&connex_temporaire);


	

	if( (initialisationConfiguration("/config/path")) != 0)
	{
		return 1;
	}

	if (pid == -1) {

		/* erreur - impossible de créer un fils */

		perror("fork error");

		exit(1);

	}
	else if (pid == 0) {

		//code du fils
		printf("processus FILS >>>> fork\n");
		if( (authentificationAvecServeur(configClient, connex_permanente) != 0){
			return 1;
		}
		
		if( (surveillerMessagePushServeur(configClient, connex_permanente) != 0){
			return 1;
		}
	}
	else{

		//code du père
		printf("processus PERE >>>> fork\n");

		if( (synchroniserAvecServeur(configClient, connex_temporaire) != 0){
		
			return 0;
		}
	}

	return 0;
}

{
	return 0;
}

	return 0;
}
