#include <stdio.h>
#include <stdlib.h>
#include "genere_arbre_binaire.h"
#include "fonctions_de_test.h"
#include "structure_arbre.h"
#include <time.h>
#include <assert.h>

// int construit_presque_complet(Arbre *a, int **src, int n){

//     if (!n)
//         return 1;

//     int nb_a_attribuer_gauche = (n-1)/2;
//     int nb_a_attribuer_droit = n - 1 - nb_a_attribuer_gauche;

//     fprintf(stderr, "valeur racine : %d\n", **src);
//     fprintf(stderr, "   nombre à attribuer à gauche : %d\n", nb_a_attribuer_gauche);
//     fprintf(stderr, "   nombre à attribuer à droite : %d\n", nb_a_attribuer_droit);

//     Noeud *noeud = alloue_noeud((**src));
//     if (!noeud)
//         return 0;

//     if (!(*a)) 
//         *a = noeud;
    

//     (*src)++;

//     if ( !construit_presque_complet(&(*a)->fg, src, nb_a_attribuer_gauche)
//         || !construit_presque_complet(&(*a)->fd, src, nb_a_attribuer_droit)){

//             detruit_arbre(*a);
//             return 0;
//         }

//     return 1;
// }

// int non_ABR_presque_complet_alea(Arbre * a, int taille){

//     int* tmp = (int*) malloc(sizeof(Noeud) * taille);

//     if (!tmp)
//         return 0;

//     int ** tab = &tmp;

//     for (int i = 0; i< taille; i++){
//         (*tab)[i] = rand() % 1000;
//     }

//     if (!construit_presque_complet(a, tab, taille))
//         return 0;


//     return 1;
// }

int construit_quelconque_aux(Arbre *a, int **codage, int* n){

    if (*n <= 0){
        *a = NULL;
        return 1;
    }

    if (**codage == -1){
        *a = NULL; 
        (*codage)++;
        (*n)--;
        return 1;
    }

    Noeud *noeud = alloue_noeud((**codage));
    if (!noeud){
        *a = NULL;
        return 0;
    }

    *a = noeud;
    (*codage)++;
    (*n)--;

    if (!construit_quelconque_aux(&((*a)->fg), codage, n)) {
        detruit_arbre(*a);
        *a = NULL;
        return 0;
    }

    if (!construit_quelconque_aux(&((*a)->fd), codage, n)) {
        detruit_arbre(*a);
        *a = NULL;
        return 0;
    }

    return 1;
}

int construit_quelconque(Arbre *a, int **codage, int n){

    if (**codage == -1){
        *a = NULL;
        return 1;
    }

    Noeud *noeud = alloue_noeud(**codage);
    if (!noeud)
        return 0;

    *a = noeud;

    // on consomme un élément donc on met à jour les variables
    // en passant à l'élément suivant
    n--;
    (*codage)++;

    if (!construit_quelconque_aux(&((*a)->fg), codage, &n)){
        fprintf(stderr, "construit_quelconque_aux a renvoyé 0");
        detruit_arbre(*a);
        return 0;
    }
    if (!construit_quelconque_aux(&((*a)->fd), codage, &n)){
        fprintf(stderr, "construit_quelconque_aux a renvoyé 0");
        detruit_arbre(*a);
        return 0;
    }

    return 1;
}

static void parcours_infixe_2_prefixe_presque_complet_aux(int *prefixe, int *infixe, int prefixe_n, int* infixe_n){

    if (prefixe_n == 1){
        infixe[(*infixe_n)++] = *prefixe;
        return ;
    }

    int quantite_partition = (prefixe_n -1)/2;
    int tmp_gauche[quantite_partition];

    for (int i = 1; i <= (quantite_partition); i++){
        tmp_gauche[i-1] = prefixe[i];
        // fprintf(stderr, "%d\n", tmp_gauche[i-1]);
    }

    int *tab_gauche = tmp_gauche;

    parcours_infixe_2_prefixe_presque_complet_aux(tab_gauche, infixe, (prefixe_n - 1) / 2, infixe_n);

    infixe[(*infixe_n)++] = prefixe[0]; 

    int tmp_droit[quantite_partition];

    // On a finit de parcourir la première partition du type [racine, p1, p2];
    //  on parcourt maintenant la deuxième, d'où le offset de i + quantite_partition
    for (int i = 1; i <= (quantite_partition); i++){
        tmp_droit[i-1] = prefixe[i + quantite_partition];
    }
    int *tab_droit = tmp_droit;

    parcours_infixe_2_prefixe_presque_complet_aux(tab_droit, infixe, (prefixe_n - 1) / 2, infixe_n);

}

void parcours_infixe_2_prefixe_presque_complet(int *prefixe, int *infixe, int n){
    int infixe_n = 0;
    parcours_infixe_2_prefixe_presque_complet_aux(prefixe, infixe, n, &infixe_n);
}

void parcours_infixe_2_prefixe_filiforme_aleatoire(int *prefixe, int* infixe, int n){

    assert(n>0);

    char forme[n];

    for (int i = 0; i < n-1 ; i++){
        int direction = rand()%2;

        // direction gauche
        if (direction == 0) {
            forme[i] = 'g';
            fprintf(stderr, "%c ", forme[i]);
        }

        // direction droite
        if (direction == 1) {
            forme[i] = 'd';
            fprintf(stderr, "%c ", forme[i]);
        }
    }

    forme[n-1] = '\0';
    char *codage = forme;

    int indice_gauche = 0;
    int indice_droit = n-1;
    int i = 0;
    while (i < n){

        if (codage[i] == 'd'){
            prefixe[i] = infixe[indice_gauche++];
        }

        if (codage[i] == 'g'){
            prefixe[i] = infixe[indice_droit--];
        }

        i++;
    }

    // ajout du dernier élément restant
    prefixe[n-1] = infixe[indice_gauche]; // choisir l'indice droit aurait été équivalent puisque les deux tombent sur la même valeur à la fin

    return ;
}

