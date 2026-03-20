#include "structure_arbre.h"
#include <stdio.h>
#include <stdlib.h>

Noeud* alloue_noeud(int val){

    Noeud* noeud = (Noeud*) malloc(sizeof(Noeud));

    if (!noeud){
        printf("Impossibilité d'allouer le noeud.");
        exit(1);
    }

    noeud->fd = NULL;
    noeud->fg = NULL;

    noeud->valeur = val;

    return noeud;

}

void detruit_arbre(Noeud *noeud) {
    if (!noeud)
        return;
    else {
        detruit_arbre(noeud->fg);
        detruit_arbre(noeud->fd);
        free(noeud);
    }
}