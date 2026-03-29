#ifndef EST_ABR_H
#define EST_ABR_H

#include "genere_arbre_binaire.h"

/* Renvoie la valeur minimale de l'arbre a. */
int abr_min(Arbre a, long long *nb_min);

/* Renvoie la valeur maximale de l'arbre a. */
int abr_max(Arbre a, long long *nb_max);

/* Affiche le min, le max et les résultats des trois méthodes sur l'arbre a. */
void affiche_infos(Arbre a);

/* Vérifie si a est un ABR par méthode naïve. */
int est_abr_naif(Arbre a, long long *nb_visites);

/* Auxiliaire de est_abr_definition. */
int est_abr_definition_aux(Arbre a, int *min, int *max, long long *nb_visites);

/* Vérifie si a est un ABR par la méthode des intervalles. */
int est_abr_definition(Arbre a, long long *nb_visites);

/* Auxiliaire de est_abr_infixe. */
int infixe_croissant(Arbre a, Noeud **dernier_noeud, long long *nb_visites);

/* Vérifie si a est un ABR par parcours infixe. */
int est_abr_infixe(Arbre a, long long *nb_visites);

#endif