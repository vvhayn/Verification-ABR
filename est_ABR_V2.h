#ifndef EST_ABR_H
#define EST_ABR_H

#include <limits.h>

typedef struct noeud {
    int valeur;
    struct noeud *fg;
    struct noeud *fd;
} Noeud;

typedef Noeud *Arbre;

Arbre alloue_noeud(int val);

int abr_max(Arbre a, long long *nb_max);
int abr_min(Arbre a, long long *nb_min);

int est_abr_naif(Arbre a, long long *nb_visites);

int est_abr_definition_aux(Arbre a, int *min, int *max, long long *nb_visites);
int est_abr_definition(Arbre a);

void affiche_infos(Arbre a);

#endif