#ifndef H_CLIENT
#define H_CLIENT
#include "ConnexionClient.h"

/* Client.h */

struct config_client {
	unsigned long idUtilisateur;
	unsigned char compteurSynchronisation;
	int idSession;
	char *cheminRepertoireConfig;
	char *cheminRpertoireClient;
}config_client;

int initialisationConfiguration(char *chemin);
int authentificationAvecServeur(config_client *configClient, config_connex *configConexion);
int surveillerRepertoireUtilisateur(config_client *configClient, config_connex *configConexion);
int surveillerMessagePushServeur(config_client *configClient, config_connex *configConexion);
int deconnexionServeur(config_client *configClient, config_connex *configConexion);
int synchroniserAvecServeur(config_client *configClient, config_connex *configConexion);
int creationFichier(config_client *configClient, config_connex *configConexion);
int suppressionFichier(config_client *configClient, config_connex *configConexion);
int recuperationFichier(config_client *configClient, config_connex *configConexion);
int miseAJourFichier(config_client *configClient, config_connex *configConexion);
#endif 
