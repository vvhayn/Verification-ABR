#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "est_ABR.h"

int abr_max(Arbre a){
    // assert(a != NULL);

    while (a->fg != NULL){
        a = a->fg;
    }
    return a->valeur;
}

int abr_min(Arbre a){
    // assert(a != NULL);

    while (a->fd != NULL){
        a = a->fd;
    }
    return a->valeur;
}

int est_abr_naif(Arbre a){
    if (abr_max(a->fg) > a->valeur && abr_min(a->fg) < a->valeur) 
        return 1;
    return 0;
}
