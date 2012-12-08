#ifndef H_SERVEUR
#define H_SERVEUR

char *cheminRepertoireConfig;

int initialisationConfiguration(char *cheminRepertoireConfig, config_traitement *configTrait);
int demarrageServer(config_connex *configConexion);
int ecouteRequete(config_connex *configConexion);
int traitementSynchronisation(config_connex *configConexion, config_traitement *configTrait, listeClient *liste);
int traitementCreationFichier(config_connex *configConexion, config_traitement *configTrait, listeClient *liste);
int traitementSuppressionFichier(config_connex *configConexion, config_traitement *configTrait, listeClient *liste);
int traitementAuthentification(config_connex *configConexion, config_traitement *configTrait, listeClient *liste);
int etablissementLiaisonPermanente(config_connex *configConexion, config_traitement *configTrait, listeClient *liste);
int traitementCreationDossier(config_connex *configConexion, config_traitement *configTrait, listeClient *liste);
int traitementSuppressionDossier(config_connex *configConexion, config_traitement *configTrait, listeClient *liste);
int traitementCreationFichier(config_connex *configConexion, config_traitement *configTrait, listeClient *liste);
int traitementRecuperationFichier(config_connex *configConexion, config_traitement *configTrait, listeClient *liste);
int traitementMiseAJour(config_connex *configConexion, config_traitement *configTrait, listeClient *liste);

#endif
