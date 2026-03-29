#ifndef EST_ABR_H
#define EST_ABR_H

typedef struct noeud {
    int valeur;
    struct noeud *fg;
    struct noeud *fd;
} Noeud;

typedef Noeud *Arbre;

int abr_max(Arbre a);
int abr_min(Arbre a);
int est_abr_naif(Arbre a);

#endif