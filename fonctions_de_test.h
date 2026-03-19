#ifndef FONCTIONS_DE_TEST_H
    #define FONCTIONS_DE_TEST_H

    #include "structure_arbre.h"

    /* Calcule la hauteur de l'arbre A.*/
    int hauteur(Arbre a);

    /* Calcule le nombre de noeuds de l'arbre A.*/
    int nb_noeuds(Arbre a);

    /* Calcule le nombre de feuilles de l'arbre A.*/
    int nb_feuilles(Arbre a);

    /* Calcule le nombre de noeuds internes de l'arbre A 
        (y compris la racine)*/
    int nb_internes(Arbre a);

#endif