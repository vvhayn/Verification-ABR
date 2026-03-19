#ifndef STRUCTURE_ARBRE_H
    #define STRUCTURE_ARBRE_H
    typedef struct noeud {
        int valeur ;
        struct noeud * fg , * fd ;
        } Noeud , * Arbre ;
		
#endif