#ifndef EST_ABR_H
#define EST_ABR_H

#include "genere_arbre_binaire.h"

/* Renvoie la plus petite étiquette de l'ABR a */
int abr_min(Arbre a, long long *nb_min);

/* Renvoie la plus grande étiquette de l'ABR a */
int abr_max(Arbre a, long long *nb_max);

void affiche_infos(Arbre a);

int est_abr_naif(Arbre a, long long *nb_visites);

int est_abr_definition_aux(Arbre a, int *min, int *max, long long *nb_visites);

int est_abr_definition(Arbre a, long long *nb_visites);

int infixe_croissant(Arbre a, Noeud **dernier_noeud, long long * nb_visites);

int est_abr_infixe(Arbre a, long long * nb_visites);

#endif