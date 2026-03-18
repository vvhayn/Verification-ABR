#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "est_ABR.h"

Arbre alloue_noeud(int val){
    Noeud* noeud = (Noeud*) malloc(sizeof(Noeud));
    if (noeud == NULL){
        return NULL; // Allocation error
    }
    noeud->valeur = val;
    noeud->fg = NULL;
    noeud->fd = NULL;
    return noeud;
}

int abr_max(Arbre a, long long * nb_max){
    assert(a != NULL);
    while (a->fd != NULL){
        a = a->fd;
        (*nb_max) += 1;
    }
    return a->valeur;
}

int abr_min(Arbre a, long long * nb_min){
    assert(a != NULL);
    while (a->fg != NULL){
        a = a->fg;
        (*nb_min) += 1;
    }
    return a->valeur;
}

int est_abr_naif(Arbre a, long long *nb_visites){
    if (a == NULL) return 1;
    (*nb_visites)++;

    if (a->fg != NULL && abr_max(a->fg, nb_visites) > a->valeur)
        return 0;
    if (a->fd != NULL && abr_min(a->fd, nb_visites) < a->valeur)
        return 0;

    return est_abr_naif(a->fg, nb_visites) && est_abr_naif(a->fd, nb_visites);
}

int est_abr_definition_aux(Arbre a, int *min, int *max, long long *nb_visites) {
    if (a == NULL)
        return 1;
    (*nb_visites)++;
    if (a->valeur > *max || a->valeur < *min)
        return 0;
    return est_abr_definition_aux(a->fd, &a->valeur, max, nb_visites) 
        && est_abr_definition_aux(a->fg, min, &a->valeur, nb_visites);
}

int est_abr_definition(Arbre a, long long *nb_visites) {
    int min = INT_MIN;
    int max = INT_MAX;
    return est_abr_definition_aux(a, &min, &max, nb_visites);
}

int infixe_croissant(Arbre a, Noeud **dernier_noeud) {
    if (a == NULL)
        return 1;
    if (!infixe_croissant(a->fg, dernier_noeud))
        return 0;
    if (*dernier_noeud != NULL && (*dernier_noeud)->valeur > a->valeur)
        return 0;
    *dernier_noeud = a;
    return infixe_croissant(a->fd, dernier_noeud);
}

int est_abr_infixe(Arbre a){
    Noeud * noeud = NULL;
    if(infixe_croissant(a, &noeud))
        return 1;
    return 0;
}

void affiche_infos(Arbre a) {
    long long tmp = 0;
    printf("La plus petite étiquette de l'arbre est : %d\n", abr_min(a, &tmp));
    tmp = 0;
    printf("La plus grande étiquette de l'arbre est : %d\n", abr_max(a, &tmp));
    tmp = 0;
    printf("L'arbre %s\n", est_abr_definition(a, &tmp) == 1 ? "est un ABR" : "n'est pas un ABR");
    printf("L'arbre %s\n", est_abr_infixe(a) == 1 ? "est un ABR" : "n'est pas un ABR");
    printf("Le nombre de visites pour déterminer si c'est un ABR est : %lld\n", tmp);
}

int main(void){
    /* Arbre a : non-ABR */
    Arbre a = alloue_noeud(1);
    a->fg         = alloue_noeud(2);
    a->fg->fd     = alloue_noeud(42);

    /* Arbre b : ABR */
    Arbre b = alloue_noeud(10);
    b->fg         = alloue_noeud(5);
    b->fg->fg     = alloue_noeud(2);
    b->fg->fd     = alloue_noeud(7);
    b->fd         = alloue_noeud(20);
    b->fd->fg     = alloue_noeud(15);
    b->fd->fd     = alloue_noeud(30);

    printf("Arbre a :\n");
    affiche_infos(a);

    printf("\nArbre b :\n");
    affiche_infos(b);

    return 0;
}

