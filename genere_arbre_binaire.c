#include <stdio.h>
#include <stdlib.h>
#include "genere_arbre_binaire.h"
#include "fonctions_de_test.h"
// #include "structure_arbre.h"
#include <time.h>
#include <assert.h>
// #include <math.h>

Noeud* alloue_noeud(int val){

    Noeud* noeud = (Noeud*) malloc(sizeof(Noeud));

    if (!noeud){
        printf("Impossibilité d'allouer le noeud.");
        exit(1);
    }

    noeud->fd = NULL;
    noeud->fg = NULL;

    noeud->valeur = val;

    return noeud;

}

void detruit_arbre(Noeud *noeud) {
    if (!noeud)
        return;
    else {
        detruit_arbre(noeud->fg);
        detruit_arbre(noeud->fd);
        free(noeud);
    }
}

int construit_quelconque_aux(Arbre *a, int **codage, int* n){

    if (*n <= 0){
        *a = NULL;
        return 1;
    }

    if (**codage == -1){
        *a = NULL; 
        (*codage)++;
        (*n)--;
        return 1;
    }

    Noeud *noeud = alloue_noeud((**codage));
    if (!noeud){
        *a = NULL;
        return 0;
    }

    *a = noeud;
    (*codage)++;
    (*n)--;

    if (!construit_quelconque_aux(&((*a)->fg), codage, n)) {
        detruit_arbre(*a);
        *a = NULL;
        return 0;
    }

    if (!construit_quelconque_aux(&((*a)->fd), codage, n)) {
        detruit_arbre(*a);
        *a = NULL;
        return 0;
    }

    return 1;
}

int construit_quelconque(Arbre *a, int **codage, int n){

    if (**codage == -1){
        *a = NULL;
        return 1;
    }

    Noeud *noeud = alloue_noeud(**codage);
    if (!noeud)
        return 0;

    *a = noeud;

    // on consomme un élément donc on met à jour les variables
    // en passant à l'élément suivant
    n--;
    (*codage)++;

    if (!construit_quelconque_aux(&((*a)->fg), codage, &n)){
        // fprintf(stderr, "construit_quelconque_aux a renvoyé 0");
        detruit_arbre(*a);
        return 0;
    }
    if (!construit_quelconque_aux(&((*a)->fd), codage, &n)){
        // fprintf(stderr, "construit_quelconque_aux a renvoyé 0");
        detruit_arbre(*a);
        return 0;
    }

    return 1;
}

/*Fonction faite par IA*/
int log2_floor_optimized(unsigned int n) {
    if (n == 0) {
        return -1;
    }

    int k = 0;

    if (n >> 16) { k += 16; n >>= 16; }
    if (n >>  8) { k +=  8; n >>=  8; }
    if (n >>  4) { k +=  4; n >>=  4; }
    if (n >>  2) { k +=  2; n >>=  2; }
    if (n >>  1) { k +=  1; }

    return k;
}

static int nombre_noeuds_gauche(int n){

    if (n<=1)
        return 0;

    int h = log2_floor_optimized(n);

    int pow_2_h_minus_1 = 1;
    for (int i = 1; i <= h-1; i++){
        pow_2_h_minus_1 *= 2;
    }

    int nb_noeuds_dernier_etage = n - (pow_2_h_minus_1 * 2) + 1;

    int capacite_gauche_dernier_etage = pow_2_h_minus_1;
    // int capacite_gauche_dernier_etage = pow(2, h-1);

    // // est-ce que le nombre de noeuds est supérieur à la capacité gauche du dernier étage ? (incomplet sur la partie droite)
    // // si oui, renvoyer la moitié de la capacité du dernier étage, sinon renvoyer le nombre de noeuds (car incomplet sur la partie gauche)
    // int sous_res =  nb_noeuds_dernier_etage < capacite_gauche_dernier_etage ? nb_noeuds_dernier_etage : capacite_gauche_dernier_etage;

    // on renvoie les noeuds du plus grand arbre complet faisable + l'étage incomplet
    int nb_noeuds_gauche = (pow_2_h_minus_1 - 1) +
                          (nb_noeuds_dernier_etage < capacite_gauche_dernier_etage
                           ? nb_noeuds_dernier_etage
                           : capacite_gauche_dernier_etage);

    return nb_noeuds_gauche;
}

static void parcours_infixe_2_prefixe_presque_complet_aux(int *prefixe, int *infixe, int n, int* prefixe_n){

    //arbre vide
    if (n <= 0) 
        return ;

    int quantite_partition_gauche = nombre_noeuds_gauche(n);

    prefixe[(*prefixe_n)++] = infixe[quantite_partition_gauche]; 

    parcours_infixe_2_prefixe_presque_complet_aux(prefixe, infixe, quantite_partition_gauche, prefixe_n);

    int quantite_partition_droite = n - 1 - quantite_partition_gauche;

    parcours_infixe_2_prefixe_presque_complet_aux(prefixe, infixe + 1 + quantite_partition_gauche, quantite_partition_droite, prefixe_n);

}

static void parcours_infixe_2_prefixe_presque_complet(int *prefixe, int *infixe, int n){
    int prefixe_n = 0;
    parcours_infixe_2_prefixe_presque_complet_aux(prefixe, infixe, n, &prefixe_n);
}

static void parcours_infixe_2_prefixe_filiforme_aleatoire(int *prefixe, int* infixe, int n){

    assert(n>0);

    char forme[n];

    for (int i = 0; i < n-1 ; i++){
        int direction = rand()%2;

        // direction gauche
        if (direction == 0) {
            forme[i] = 'g';
            // fprintf(stderr, "%c ", forme[i]);
        }

        // direction droite
        if (direction == 1) {
            forme[i] = 'd';
            // fprintf(stderr, "%c ", forme[i]);
        }
    }

    forme[n-1] = '\0';
    char *codage = forme;

    int indice_gauche = 0;
    int indice_droit = n-1;
    int i_codage = 0; // peut aller jusqu'à n dans la boucle
    int i_prefixe = 0; // peut aller jusqu'à 2*n+1 dans la boucle
    while (i_codage < (n - 1)){ // on ajoute le dernier élément séparement car le caractère 'codage' correspondant est '\0' 

        if (codage[i_codage] == 'd'){
            prefixe[i_prefixe++] = infixe[indice_gauche++];
            prefixe[i_prefixe++] = -1;
        }

        if (codage[i_codage] == 'g'){
            prefixe[i_prefixe++] = infixe[indice_droit--];
        }

        i_codage++;
    }

    // ajout du dernier élément restant
    prefixe[i_prefixe] = infixe[indice_gauche]; // choisir l'indice droit aurait été équivalent puisque les deux tombent sur la même valeur à la fin
    // i_codage++;
    i_prefixe++;

    int taille_codage = 2*n + 1;
    while (i_prefixe < taille_codage){
        prefixe[i_prefixe++] = -1;
    }
    return ;
}

static void parcours_infixe_2_prefixe_quelconque_aleatoire_aux(int * prefixe, int * infixe, int n, int *i_pref){
    // if (n == 1){
    //     prefixe[(*i_pref)++] = infixe[0];
    //     return ;
    // }

    if (n == 0){
        prefixe[(*i_pref)++] = -1;
        return ;
    }

    int k = rand()%n;

    prefixe[(*i_pref)++] = infixe[k];

    parcours_infixe_2_prefixe_quelconque_aleatoire_aux(prefixe, infixe, k, i_pref);
    parcours_infixe_2_prefixe_quelconque_aleatoire_aux(prefixe, infixe + k+1, n-k-1, i_pref);
}

// static 
void parcours_infixe_2_prefixe_quelconque_aleatoire(int * prefixe, int * infixe, int n){

    int h = 0;
    parcours_infixe_2_prefixe_quelconque_aleatoire_aux(prefixe, infixe, n, &h);
}

static int verif_presence(int tab[], int taille, int x){
    for (int i = 0; i < taille; i++){
        if (tab[i] == x)
            return 0;
    }
    return 1;
}

int ABR_presque_complet_alea(Arbre * a, int taille){
    assert(taille >=0);
    
    int taille_codage = 2*taille+1;
    int tab[taille_codage];
    int i = 0;
    int somme = 0;
    while (i < taille_codage){
        
        int k = rand()%100000;
        if (!verif_presence(tab, i, k + 1))
            continue;

        somme += k + 1;
        tab[i++] = -1;
        tab[i++] = somme;

    }
    
    // ALTERNER -1 ET UNE VALEUR

    int *infixe = tab;

    int p[taille_codage];
    // for (int i =0; i < taille_codage; i++){
    //     p[i] = -1;
    // }
    int *prefixe = p;

    // fprintf(stderr, "parcours infixe avant la création du prefixe : ");
    // for (int i = 0; i < taille_codage; i++){
    //     fprintf(stderr, "%d ", infixe[i]);
    // }
    // fprintf(stderr, "\n");
    
    parcours_infixe_2_prefixe_presque_complet(prefixe, infixe, taille_codage);

    // fprintf(stderr, "parcours prefixe : ");
    // for (int i = 0; i < taille_codage; i++){
    //     fprintf(stderr, "%d ", prefixe[i]);
    // }
    // fprintf(stderr, "\n");

    if (!construit_quelconque(a, &prefixe, taille_codage))
        return 0;

    return 1;
}

int non_ABR_presque_complet_alea(Arbre * a, int taille){
    assert(taille >=0);
    
    // fprintf(stderr, "non_abr");
    int taille_codage = 2*taille+1;
    int tab[taille_codage];
    int i = 0;
    int somme = 0;
    while (i < taille_codage){

        

        int k = rand()%100000;
        if (!verif_presence(tab, i, k + 1))
            continue;

        // on divise la taille par 2 afin de ne pas avoir un parcours infixe linéaire
        if (i%4 == 0){
            // fprintf(stderr, "division");
            somme = somme/2;
        }
        else 
            somme += k + 1;
        tab[i++] = -1;
        tab[i++] = somme;
    }
    
    // ALTERNER -1 ET UNE VALEUR

    int *infixe = tab;

    int p[taille_codage];
    // for (int i =0; i < taille_codage; i++){
    //     p[i] = -1;
    // }
    int *prefixe = p;

    // fprintf(stderr, "parcours infixe avant la création du prefixe : ");
    // for (int i = 0; i < taille_codage; i++){
    //     fprintf(stderr, "%d ", infixe[i]);
    // }
    // fprintf(stderr, "\n");
    
    parcours_infixe_2_prefixe_presque_complet(prefixe, infixe, taille_codage);

    // fprintf(stderr, "parcours prefixe : ");
    // for (int i = 0; i < taille_codage; i++){
    //     fprintf(stderr, "%d ", prefixe[i]);
    // }
    // fprintf(stderr, "\n");

    if (!construit_quelconque(a, &prefixe, taille_codage))
        return 0;

    return 1;
}

int ABR_filiforme_alea(Arbre * a, int taille){

    assert(taille >=0);
    
    int taille_codage = 2*taille+1;
    int tab[taille];
    int i = 0;
    int somme = 0;
    while (i < taille){

        

        int k = rand()%30;
        if (!verif_presence(tab, i, somme + k + 1))
            continue;

        somme += k + 1;
        // tab[i++] = -1;
        tab[i++] = somme;

    }
    
    // ALTERNER -1 ET UNE VALEUR

    int *infixe = tab;

    int p[taille_codage];
    // for (int i =0; i < taille_codage; i++){
    //     p[i] = -1;
    // }
    int *prefixe = p;

    // fprintf(stderr, "parcours infixe avant la création du prefixe : ");
    // for (int i = 0; i < taille; i++){
    //     fprintf(stderr, "%d ", infixe[i]);
    // }
    // fprintf(stderr, "\n");
    
    parcours_infixe_2_prefixe_filiforme_aleatoire(prefixe, infixe, taille);

    // fprintf(stderr, "parcours prefixe : ");
    // for (int i = 0; i < taille_codage; i++){
    //     fprintf(stderr, "%d ", prefixe[i]);
    // }
    // fprintf(stderr, "\n");

    if (!construit_quelconque(a, &prefixe, taille_codage))
        return 0;

    return 1;

}

int non_ABR_filiforme_alea(Arbre * a, int taille){

    assert(taille >=0);
    
    int taille_codage = 2*taille+1;
    int tab[taille];
    int i = 0;
    int somme = 0;
    while (i < taille){

        

        int k = rand()%100000;
        if (!verif_presence(tab, i, somme + k + 1))
            continue;

        if (i%2 == 0){
            // fprintf(stderr, "division");
            somme = somme/2;
        }
        else 
            somme += k + 1;

        // somme += k;
        // tab[i++] = -1;
        tab[i++] = somme;

    }
    
    // ALTERNER -1 ET UNE VALEUR

    int *infixe = tab;

    int p[taille_codage];
    // for (int i =0; i < taille_codage; i++){
    //     p[i] = -1;
    // }
    int *prefixe = p;

    // fprintf(stderr, "parcours infixe avant la création du prefixe : ");
    // for (int i = 0; i < taille; i++){
    //     fprintf(stderr, "%d ", infixe[i]);
    // }
    // fprintf(stderr, "\n");
    
    parcours_infixe_2_prefixe_filiforme_aleatoire(prefixe, infixe, taille);

    // fprintf(stderr, "parcours prefixe : ");
    // for (int i = 0; i < taille_codage; i++){
    //     fprintf(stderr, "%d ", prefixe[i]);
    // }
    // fprintf(stderr, "\n");

    if (!construit_quelconque(a, &prefixe, taille_codage))
        return 0;

    return 1;

}

int ABR_quelconque_alea(Arbre * a, int taille){

    assert(taille >=0);
    
    int taille_codage = 2*taille+1;
    int tab[taille];
    int i = 0;
    int somme = 0;
    while (i < taille){
        int k = rand()%100000;
        if (!verif_presence(tab, i, k + 1))
            continue;

        somme += k + 1; // le +1 évite les doublon
        tab[i++] = somme;
    }
    
    int *infixe = tab;
    int p[taille_codage];
    int *prefixe = p;

    // fprintf(stderr, "parcours infixe avant la création du prefixe : ");
    // for (int i = 0; i < taille; i++){
    //     fprintf(stderr, "%d ", infixe[i]);
    // }
    // fprintf(stderr, "\n");

    parcours_infixe_2_prefixe_quelconque_aleatoire(prefixe, infixe, taille);

    // fprintf(stderr, "parcours prefixe : ");
    // for (int i = 0; i < taille_codage; i++){
    //     fprintf(stderr, "%d ", prefixe[i]);
    // }
    // fprintf(stderr, "\n");

    if (!construit_quelconque(a, &prefixe, taille_codage))
        return 0;

    return 1;
}

int non_ABR_quelconque_alea(Arbre * a, int taille){

    assert(taille >=0);
    
    int taille_codage = 2*taille+1;
    int tab[taille];
    int i = 0;
    int somme = 0;
    while (i < taille){
        int k = rand()%100000;
        if (!verif_presence(tab, i, k + 1))
            continue;

        if (i%2 == 0){
            // fprintf(stderr, "division");
            somme = somme/2;
        }
        else 
            somme += k + 1; // le +1 évite les doublons
        tab[i++] = somme;
    }
    
    int *infixe = tab;
    int p[taille_codage];
    int *prefixe = p;

    // fprintf(stderr, "parcours infixe avant la création du prefixe : ");
    // for (int i = 0; i < taille; i++){
    //     fprintf(stderr, "%d ", infixe[i]);
    // }
    // fprintf(stderr, "\n");

    parcours_infixe_2_prefixe_quelconque_aleatoire(prefixe, infixe, taille);

    // fprintf(stderr, "parcours prefixe : ");
    // for (int i = 0; i < taille_codage; i++){
    //     fprintf(stderr, "%d ", prefixe[i]);
    // }
    // fprintf(stderr, "\n");

    if (!construit_quelconque(a, &prefixe, taille_codage))
        return 0;

    return 1;
}