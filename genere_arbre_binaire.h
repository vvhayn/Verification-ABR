#ifndef GENERE_ARBRE_BINAIRE_H
    #define GENERE_ARBRE_BINAIRE_H
    
    typedef struct noeud {
        int valeur ;
        struct noeud * fg , * fd ;
        } Noeud , * Arbre ;
		

    /*allocation d'un noeud, mise des enfants
    à NULL; renvoie NULL si non-alloué*/
    Noeud* alloue_noeud(int val);

    void detruit_arbre(Noeud *noeud);


    int non_ABR_presque_complet_alea(Arbre * a, int taille);

    int construit_quelconque(Arbre *a, int **codage, int n);


    // void parcours_infixe_2_prefixe_presque_complet(int *prefixe, int *infixe, int n);

    // /*Nécessite de faire un appel srand(time(NULL)) pour cette fonction; infixe et prefixe
    // doivent être de la même taille*/
    // void parcours_infixe_2_prefixe_filiforme_aleatoire(int *prefixe, int* infixe, int n);

    // /*Nécessite de faire un appel srand(time(NULL)) pour cette fonction;
    // si infixe est de taille n, alors prefixe doit être de taille 2n + 1*/
    // void parcours_infixe_2_prefixe_quelconque_aleatoire(int * prefixe, int * infixe, int n);

    /*nécessite rand*/
    int ABR_presque_complet_alea(Arbre * a, int taille);

    /* nécessite rand*/
    int non_ABR_presque_complet_alea(Arbre * a, int taille);

    int ABR_filiforme_alea(Arbre * a, int taille);

    int non_ABR_filiforme_alea(Arbre * a, int taille);

    int ABR_quelconque_alea(Arbre * a, int taille);

    // void parcours_infixe_2_prefixe_quelconque_aleatoire(int * prefixe, int * infixe, int n);
    int non_ABR_quelconque_alea(Arbre * a, int taille);

#endif
