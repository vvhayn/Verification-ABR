#ifndef STRUCTURE_ARBRE_H
    #define STRUCTURE_ARBRE_H
    
    typedef struct noeud {
        int valeur ;
        struct noeud * fg , * fd ;
        } Noeud , * Arbre ;
		


    /*allocation d'un noeud, mise des enfants
    à NULL; renvoie NULL si non-alloué*/
    Noeud* alloue_noeud(int val);
    
    void detruit_arbre(Noeud *noeud);

#endif
