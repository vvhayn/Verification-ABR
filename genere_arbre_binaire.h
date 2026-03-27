#ifndef GENERE_ARBRE_BINAIRE_H
    #define GENERE_ARBRE_BINAIRE_H
    
    #include "structure_arbre.h"
    
    int construit_presque_complet(Arbre *a, int **src, int n);

    int non_ABR_presque_complet_alea(Arbre * a, int taille);

    int construit_quelconque(Arbre *a, int **codage, int n);

    void detruit_arbre(Noeud *noeud);

    void parcours_infixe_2_prefixe_presque_complet(int *prefixe, int *infixe, int n);

    /*Nécessite de faire un appel srand(time(NULL)) pour cette fonction; infixe et prefixe
    doivent être de la même taille*/
    void parcours_infixe_2_prefixe_filiforme_aleatoire(int *prefixe, int* infixe, int n);

    /*Nécessite de faire un appel srand(time(NULL)) pour cette fonction;
    si infixe est de taille n, alors prefixe doit être de taille 2n + 1*/
    void parcours_infixe_2_prefixe_quelconque_aleatoire(int * prefixe, int * infixe, int n);

    int ABR_presque_complet_alea(Arbre * a, int taille);


#endif
