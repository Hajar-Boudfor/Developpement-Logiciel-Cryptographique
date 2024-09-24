#include "gmp.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>



#define Mauvais_Parametre 1 

int main( int argc, char* argv[]){

	if(argc!= 3){
		printf("Mauvais nombre de parametre");
		return Mauvais_Parametre ;
	}

	unsigned int k = atoi(argv[1]);
	unsigned int x = atoi(argv[2]);

//Création du générateur aléatoire 
	gmp_randstate_t generateur ;
	gmp_randinit_default(generateur);

//Spécification d'une graine au générateur
	mpz_t seed ;
	mpz_init_set_ui(seed, time(x));
	gmp_randseed(generateur, seed);
        gmp_printf("la graine utlisé : %Zd \n",seed);




    int compteur = 0;
	mpz_t rop ;
	mpz_init(rop) ;


	while(1){

		mpz_urandomb(rop, generateur, k);
		gmp_printf("Le nombre généré numéros %d: %Zd \n", ++compteur, rop);

		
		if( mpz_divisible_ui_p(rop, 20)){

			printf("Divisible par 20!");
			break;
		}
   }

	mpz_clear(seed);
	mpz_clear(rop);
	gmp_randclear(generateur);

	return 0 ;

}
