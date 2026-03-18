#ifndef EST_ABR_H
#define EST_ABR_H

typedef struct noeud {
    int valeur;
    struct noeud *fd, *fg;
} Noeud, *Arbre;

Arbre alloue_noeud(int val);

/* Renvoie la plus petite étiquette de l'ABR a */
int abr_min(Arbre a, long long *nb_min);

/* Renvoie la plus grande étiquette de l'ABR a */
int abr_max(Arbre a, long long *nb_max);

void affiche_infos(Arbre a);

#endif