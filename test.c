#include <stdio.h>
#include <math.h>

static int taille_sous_arbre_gauche(int n) {
    if (n <= 1) return 0;

    int h = 0;
    int tmp = n;
    while (tmp > 1) { tmp >>= 1; h++; }
    // h = floor(log2(n))

    int capacite_dernier_niveau    = 1 << h;           // 2^h
    int noeuds_dernier_niveau      = n - (capacite_dernier_niveau - 1);
    int capacite_gauche_dernier    = 1 << (h - 1);     // 2^(h-1)

    // Le sous-arbre gauche prend au plus sa moitié du dernier niveau
    int noeuds_gauche_dernier = noeuds_dernier_niveau < capacite_gauche_dernier
                                ? noeuds_dernier_niveau
                                : capacite_gauche_dernier;
        fprintf(stderr, "taille du sous arbre gauche pour un arbre à %d noeuds : %d\n", n, noeuds_gauche_dernier);

    return (capacite_gauche_dernier - 1) + noeuds_gauche_dernier;
}

static int nombre_noeuds_gauche(int n){

    assert(n>0);

    if (n<=1)
        return 0;

    int h = floor(log2(n));

    int nb_noeuds_dernier_etage = n - pow(2, h) + 1;

    int capacite_gauche_dernier_etage = pow(2, h-1);


    int sous_res =  nb_noeuds_dernier_etage < capacite_gauche_dernier_etage ? nb_noeuds_dernier_etage : capacite_gauche_dernier_etage;

    // est-ce que le nombre de noeuds est supérieur à la capacité gauche du dernier étage ? (incomplet sur la partie droite)
        // si oui, renvoyer la moitié de la capacité du dernier étage, sinon renvoyer le nombre de noeuds (car incomplet sur la partie gauche)
    return (pow(2, h - 1) - 1) + sous_res;
}

static void aux(int *prefixe, int *infixe, int n, int *infixe_n) {
    if (n == 0) return;
    if (n == 1) {
        infixe[(*infixe_n)++] = prefixe[0];   // feuille
        return;
    }

    int tg = nombre_noeuds_gauche(n);
    int td = n - 1 - tg;

    // Sous-arbre gauche : éléments prefixe[1..tg]
    aux(prefixe + 1, infixe, tg, infixe_n);

    // Racine
    infixe[(*infixe_n)++] = prefixe[0];

    // Sous-arbre droit : éléments prefixe[tg+1..n-1]
    aux(prefixe + 1 + tg, infixe, td, infixe_n);
}

void parcours_prefixe_2_infixe(int *prefixe, int *infixe, int n) {
    int infixe_n = 0;
    aux(prefixe, infixe, n, &infixe_n);
}

int main() {
    int prefixe[7] = {4, 2, 1, 3, 6, 5, 7};  // parcours préfixe
    int infixe[7];

    parcours_prefixe_2_infixe(prefixe, infixe, 7);

    for (int i = 0; i < 7; i++) {
        printf("%d ", infixe[i]);   // attendu : 1 2 3 4 5 6 7
    }
    printf("\n");
}