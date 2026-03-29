#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "est_ABR.h"
#include "genere_arbre_binaire.h"
// #include "structure_arbre.h"
// #include "fonctions_de_test.h"
 
#define TAILLE_MIN 100
#define TAILLE_MAX 10000
#define TAILLE_STEP 1000
#define NB_REPETITIONS 50  
#define FICHIER_CSV "mesures.csv"

static const char *NOM_METHODE[] = {"Naif", "Definition", "Infixe"};
static const char *NOM_MORPHOLOGIE[] = {"ABR_PresqueComplet", "NonABR_PresqueComplet", "ABR_Filiforme", "NonABR_Filiforme", "ABR_Quelconque", "NonABR_Quelconque"};
#define NB_METHODES     3
#define NB_MORPHOLOGIES 6

/* Génère un arbre selon sa morphologie (0 à 5) */
static int genere_arbre(Arbre *a, int morph, int taille) {
    // if (morph == 0) return ABR_presque_complet_alea(a, taille);
    // if (morph == 1) return non_ABR_presque_complet_alea(a, taille);
    // if (morph == 2) return ABR_filiforme_alea(a, taille);
    // if (morph == 3) return non_ABR_filiforme_alea(a, taille);
    // if (morph == 4) return ABR_quelconque_alea(a, taille);
    // if (morph == 5) return non_ABR_quelconque_alea(a, taille);
    // return 0;

    switch(morph) {
        case 0 :
            return ABR_presque_complet_alea(a, taille);
        case 1:
            return non_ABR_presque_complet_alea(a, taille);
        case 2: 
            return ABR_filiforme_alea(a, taille);
        case 3:
            return non_ABR_filiforme_alea(a, taille);
        case 4 :
            return ABR_quelconque_alea(a, taille);
        case 5 :
            return non_ABR_quelconque_alea(a, taille);
        default : 
        return 0;
    }
}

/* Appelle la méthode de vérification m sur l'arbre a */
static int appelle_methode(Arbre a, int m, long long *nb_visites) {
    *nb_visites = 0;
    switch (m) {
        case 0: return est_abr_naif(a, nb_visites);
        case 1: return est_abr_definition(a, nb_visites);
        case 2: return est_abr_infixe(a, nb_visites);
        default: return -1;
    }
}

/* Effectue NB_REPETITIONS générations d'arbres de morphologie morph et calcule la moyenne
   Renvoie 1 si au moins une répétition a réussi, 0 sinon */
static int calcule_moyenne(int taille, int morph, int m, double *moy_visites, double *moy_temps) {
    long long total_visites = 0;
    double total_temps = 0.0;
    int n = 0;
    int nb_repetitions = (taille > 10000) ? 20 : NB_REPETITIONS; // juste pr test

    for (int rep = 0; rep < nb_repetitions; rep++) {
        Arbre a = NULL;

        // pourquoi vérifier a == NULL dans le premier if et a != NULL dans le deuxième ? 
        if (!genere_arbre(&a, morph, taille) || a == NULL) {
            if (a != NULL) detruit_arbre(a);
            continue;
        }

        // Utilisation de monotonic car sensé etre plus precis, revoir la doc 

        long long nb_visites = 0;
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);  // Début de la mesure
        appelle_methode(a, m, &nb_visites);
        clock_gettime(CLOCK_MONOTONIC, &end);    // Fin de la mesure

        // Calcul du temps écoulé en secondes
        double duree = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

        // ------------------------------------------------------------------

        total_visites += nb_visites;
        total_temps   += duree;
        n++;

        detruit_arbre(a);
    }

    if (n == 0) return 0;

    *moy_visites = (double)total_visites / n;
    *moy_temps   = total_temps / n;
    return 1;
}

int main(void) {
    srand((unsigned int)time(NULL));

    FILE *csv = fopen(FICHIER_CSV, "w");
    if (csv == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s\n", FICHIER_CSV);
        return EXIT_FAILURE;
    }

    fprintf(csv, "Taille;Morphologie;Methode;Nb_visites;Temps\n");
    printf("Debut de la générations\n");

    for (int taille = TAILLE_MIN; taille <= TAILLE_MAX; taille += TAILLE_STEP) {
        printf("Taille %d...\n", taille);
        fflush(stdout);  

        for (int morph = 0; morph < NB_MORPHOLOGIES; morph++) {
            for (int m = 0; m < NB_METHODES; m++) {
                double moy_visites = 0.0;
                double moy_temps   = 0.0;

                if (!calcule_moyenne(taille, morph, m, &moy_visites, &moy_temps))
                    continue;

                fprintf(csv, "%d;%s;%s;%.2f;%.9f\n", taille, NOM_MORPHOLOGIE[morph], NOM_METHODE[m], moy_visites, moy_temps);
                fflush(csv);
            }
        }
    }

    fclose(csv);
    printf("Terminé. Résultats dans %s\n", FICHIER_CSV);

    // pourquoi pas return 0 ? 
    return EXIT_SUCCESS;
}