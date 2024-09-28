// Ce programme génère des nombres aléatoires jusqu'à ce qu'il trouve un nombre divisible par 20.
// Il permet également de spécifier la taille des nombres générés et d'initialiser le générateur avec une graine donnée.

#include "gmp.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAUVAIS_PARAMETRE 1 

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("Mauvais nombre de paramètres.\n");
        return MAUVAIS_PARAMETRE;
    }

    unsigned int k = atoi(argv[1]);
    
    // Création du générateur aléatoire
    gmp_randstate_t generateur;
    gmp_randinit_default(generateur);

    // Spécification d'une graine pour le générateur
    mpz_t seed;
    mpz_init_set_str(seed, argv[2], 0);
    gmp_randseed(generateur, seed);
    gmp_printf("La graine utilisée : %Zd\n", seed);

    // Calcul de 2^(k-1)
    mpz_t pow2;
    mpz_init(pow2); 
    mpz_ui_pow_ui(pow2, 2, k - 1);
    
    // Calcul de 10^k et de 10^(k-1)
    mpz_t pow10, pow10_1;
    mpz_inits(pow10, pow10_1, NULL);
    mpz_ui_pow_ui(pow10, 10, k);
    mpz_ui_pow_ui(pow10_1, 10, k - 1);
        
    int compteur = 0;
    mpz_t rop;
    mpz_init(rop);

    /*
    // Génération de nombres aléatoires d'au plus k bits
    while (1) {
        mpz_urandomb(rop, generateur, k);
        gmp_printf("Le nombre généré numéro %d : %Zd\n", ++compteur, rop);
        
        if (mpz_divisible_ui_p(rop, 20)) {
            printf("\nLe nombre numéro %d est divisible par 20 !\n", compteur);
            break;
        }
    }
    */
    
    /*
    // Génération de nombres exactement égaux à k bits (appartenant à [2^(k-1), 2^k])
    while (1) {
        mpz_urandomb(rop, generateur, k - 1);
        mpz_add(rop, rop, pow2); 
        gmp_printf("Le nombre généré numéro %d : %Zd\n", ++compteur, rop);
        
        if (mpz_divisible_ui_p(rop, 20)) {
            printf("\nLe nombre numéro %d est divisible par 20 !\n", compteur);
            break;
        }
    }
    */
    
    /*
    // Génération de nombres d'au plus k chiffres décimaux (appartenant à [0, 10^k[)
    while (1) {
        mpz_urandomm(rop, generateur, pow10);
        gmp_printf("Le nombre généré numéro %d : %Zd\n", ++compteur, rop);
        
        if (mpz_divisible_ui_p(rop, 20)) {
            printf("\nLe nombre numéro %d est divisible par 20 !\n", compteur);
            break;
        }
    }
    */
    
    // Génération de nombres exactement égaux à k chiffres décimaux (appartenant à [10^(k-1), 10^k[)
    while (1) {
        mpz_urandomm(rop, generateur, pow10_1);
        mpz_add(rop, rop, pow10_1); 
        gmp_printf("Le nombre généré numéro %d : %Zd\n", ++compteur, rop);
        
        if (mpz_divisible_ui_p(rop, 20)) {
            printf("\nLe nombre numéro %d est divisible par 20 !\n", compteur);
            break;
        }
    }   
    
    // Libération de la mémoire allouée
    mpz_clears(pow10, pow10_1, pow2, seed, rop, NULL);
    gmp_randclear(generateur);

    return 0;
}
