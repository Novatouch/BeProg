#include "ConnexionServeur.h"
#include "Message.h"
#include "Serveur.h"
/*
	auteur : Philippe GAUTIER
	but : faire le traitement de la chaine de caractère recu par le serveur
	paramètres : chaine de caratère
	renvoi : 0 OK 1 NOK
*/

int traitementRequete(char *chaine)
{
    message requete_recu;

    if( (decodeMessage(chaine, &requete_recu)) != 0){

        printf("Une erreur s'est produite, message undécodable");
        return 1;
    }

    printf("user : %s", requete_recu.user);

    // orientation vers la bonne fonction de traitement
    return 0;
}





/*
	auteur :
	but :
	paramètres :
	renvoi :

*/
/*
int initialisationConfiguration(char *cheminRepertoireConfig, config_traitement *configTrait)
{
}
*/
/*
	auteur :
	but :
	paramètres :
	renvoi :

*/
/*
int demarrageServer(config_connex *configConexion)
{
}
*/
/*
	auteur :
	but :
	paramètres :
	renvoi :

*/
/*
int ecouteRequete(config_connex *configConexion)
{
}
*/
/*
	auteur :
	but :
	paramètres :
	renvoi :

*/
/*
int traitementSynchronisation(config_connex *configConexion, config_traitement *configTrait, listeClient *liste)
{
}
*/
/*
	auteur :
	but :
	paramètres :
	renvoi :

*/

/*
int traitementCreationFichier(config_connex *configConexion, config_traitement *configTrait, listeClient *liste)
{
}
*/

/*
	auteur :
	but :
	paramètres :
	renvoi :

*/
/*
int traitementSuppressionFichier(config_connex *configConexion, config_traitement *configTrait, listeClient *liste)
{
}
*/
/*
	auteur :
	but :
	paramètres :
	renvoi :

*/
/*
int traitementAuthentification(config_connex *configConexion, config_traitement *configTrait, listeClient *liste)
{
}
*/
/*
	auteur :
	but :
	paramètres :
	renvoi :

*/
/*
int etablissementLiaisonPermanente(config_connex *configConexion, config_traitement *configTrait, listeClient *liste)
{
}
*/
/*
	auteur :
	but :
	paramètres :
	renvoi :

*/
/*
int traitementCreationDossier(config_connex *configConexion, config_traitement *configTrait, listeClient *liste)
{
}
*/
/*
	auteur :
	but :
	paramètres :
	renvoi :

*/
/*
int traitementSuppressionDossier(config_connex *configConexion, config_traitement *configTrait, listeClient *liste)
{
}
*/
/*
	auteur :
	but :
	paramètres :
	renvoi :

*/
/*
int traitementCreationFichier(config_connex *configConexion, config_traitement *configTrait, listeClient *liste)
{
}
*/
/*
	auteur :
	but :
	paramètres :
	renvoi :

*/
/*
int traitementRecuperationFichier(config_connex *configConexion, config_traitement *configTrait, listeClient *liste)
{
}
*/
/*
	auteur :
	but :
	paramètres :
	renvoi :

*/
/*
int traitementMiseAJour(config_connex *configConexion, config_traitement *configTrait, listeClient *liste)
{
}
*/
