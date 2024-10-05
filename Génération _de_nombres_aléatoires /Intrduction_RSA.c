// Ce code permet de déchiffrer un message chiffré en utilisant le chiffrement RSA avec une clé de 1024 bits.

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]){
    mpz_t n, d, c, a;
    mpz_inits(n, d, c, a, NULL);

    mpz_set_ui(a, 1);

    // Initialisation des valeurs de n, d et c à partir de leurs représentations hexadécimales
    mpz_set_str(n, "ae828886a1990cde8d02955ba7ca8ee6f572d6030f947aa26d4643e5f00e824bbc7b962904f04ab5bb4682f661c2b8b86bd2c0c04b4de86aac8b9f5086e253e5d1297ece80a4d5b5b3d5f82d8ba878dc031e1a19b6af1aa3ac29c5a8df46cb3743f866311e1df3be3d62d6395633c900c7ac5138d34c825b8f37fbf70842879d", 16);
    mpz_set_str(d, "4c2500d55de59e4bed5357406af263703b612428a9bfabd2fbc351151fadf5047ef59e0bbfefe9696a91d5cb13d5172cc13f708377584335689c73a37b777e0b6c524c4a9ab7e4b78e67ee9ffd3acdb1d6dfda7c42db40eebb0901a74cf2508e5316d9227b1c09dd798f52fd335185e0958fb36271c13260a2650e3b074a5e31", 16);
    mpz_set_str(c, "96794d4b033ad45cd2b27e199aa27de76801ab04dff67cd1afd79ebd349744ff2a0b0afa2b4fb8f556a8e52d5d0c53536481bc4daf8453c9adcd473e8d9f1a74afdc6901dbce1c7b123d41e6eaf23125ccfe07da3aa69ef25794ad8779f21d605af85571f8e0dcd7b9c43d0b9033fd2c8aa01b7846010ca6985f7491db2ee9db", 16);

    char *base2 = mpz_get_str(NULL, 2, d);
    size_t k = mpz_sizeinbase(d, 2);

    // Algorithme "square and multiply" de gauche à droite pour le déchiffrement
    for (int i = k - 1; i >= 0; i--) {
        mpz_mul(a, a, a); 
        mpz_mod(a, a, n);

        if (base2[i] == '1') { 
            mpz_mul(a, a, c); 
            mpz_mod(a, a, n);
        }
    }

    // Affichage du résultat du déchiffrement
    gmp_printf("m = %Zd\n", a);

    // Libération de la mémoire
    mpz_clears(n, d, c, a, NULL);
    free(base2);

    return 0;
}
