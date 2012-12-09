/*
	auteur : 
	but : 
	paramètres :
	renvoi :

*/


int ajouterClient(liste_client *liste, unsigned int id)
{
    case_liste_client *new = malloc(sizeof(*new));
    
    if (liste == NULL || new == NULL)
    {
        exit(EXIT_FAILURE);
    }

    new->idClient = id;
    new->next = NULL;

    if (liste->first != NULL) /* liste is not empty */
    {
        /* go at the end of liste */
        case_liste_client *current = liste->first;
        while (current->next != NULL)
        {
            current = current->next; // till the last case of liste
        }
        current->next = new;
    }
    else /* liste is empty, we will add the first case*/
    {
        liste->first = new;
    }
}

/*
	auteur : 
	but : 
	paramètres :
	renvoi :

*/


int supprimerClient(liste_client *liste, unsigned int id)
{
}

/*
	auteur : 
	but : 
	paramètres :
	renvoi :

*/

int rechercherClient(liste_client *liste, unsigned int id)
{
}
