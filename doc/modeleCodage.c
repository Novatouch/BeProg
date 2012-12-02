// include 
#include <asm/unaligned.h>

// 
#ifndef H_HELLO
#define H_HELLO

/* hello.h */


#endif /* guard */

// constantes
#define ACPI_AC_CLASS			"ac_adapter"

// structure 
struct acpi_ac {
	struct power_supply charger;
	struct acpi_device * device;
unsigned long long state;
} acpi_ac;

// fonctions

/*
	auteur : 
	but : 
	paramètres :
	renvoi :

*/
static void fonction(char *m, int *base,u64 now)
{
	// declartion de plusieurs variable
	int *timer, tmp;
	unsigned long next = 0, i;
	unsigned long flags;
	
	// assignation espace autour du signe égal
	i = 0;
	
	procdure(&base->cpu_base->lock, flags);

	// retour de fonction espace autour du signe égal
	curr = timerqueue_getnext(parametre);
	/*
	* Crude but we have to do this O(N*N) thing, because
	* we have to unlock the base when printing:
	*/
	while (curr && i < next) {
		curr = timerqueue_iterate_next(curr);
		i++;
	}

	switch (Variable) {

	case Valeur1 :
		Liste d'instructions;

		break;

	case Valeur2 :
		Liste d'instructions;

		break;

	case Valeurs... :
		Liste d'instructions;

		break;

	default: 

		Liste d'instructions;

	}
	
	for (i = 0; i < 100; i++) {
	}
	
	if (i > 0) {
	
	
	}
}
