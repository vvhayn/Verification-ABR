#include "fonctions_de_test.h"

static int max( int a, int b){
    return ((a) > (b) ? (a) : (b));
} 

int hauteur(Arbre a){

    if (!a){
        return -1;
    }

    return max(1 + hauteur(a->fd), 1 + hauteur(a->fg));
}

int nb_noeuds(Arbre a){

    if (!a){
            return 0;
        }

    int nb = 1 + nb_noeuds(a->fd) + nb_noeuds(a->fg);

    return nb;
}

int nb_feuilles(Arbre a){

    if (!a)
        return 0;
    
    if (!a->fg && !a->fd){
            return 1;
        }

    // if (!a)
    //     return 0;

    return nb_feuilles(a->fg) + nb_feuilles(a->fd);

}

int nb_internes(Arbre a){

    if (!a){
            return 0;
    }

    int somme = 0;

    if (a->fg || a->fd)
        somme += 1 + nb_internes(a->fg) + nb_internes(a->fd);

    return somme;

}

