#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "est_ABR.h"
#include "genere_arbre_binaire.h"
#include "fonctions_de_test.h"
#include "structure_arbre.h"

Arbre construit_arbre(FILE* f ){
    char chara;

    // prend le prochain entier représentant un noeud 
    do {chara = fgetc(f);} while (chara != ' ');
    int c = atoi(&chara);

    // cas où c'est un noeud vide
    if (c == 0) {
        return NULL;
    }

    // racine de notre (sous-)arbre actuel
    Noeud* noeud = alloue_noeud(c);

    noeud->fg = construit_arbre(f);
    noeud->fd = construit_arbre(f);

    return noeud;
}

void ecrireDebut(FILE *f){
    fprintf(f, "digraph arbre {\n");
    fprintf(f, "    node [shape = record, height = .1 ]\n");
    fprintf(f, "    edge [tailclip = false, arrowtail = dot, dir = both];\n\n");

}

void ecrireFin(FILE *f){
    fprintf(f, "}\n");
}

void ecrireArbre(FILE *f, Arbre a){

    // arbre vide
    if (!a)
        return ;

    // noeud de l'arbre
    fprintf(f, "    n%p [label=\"<gauche> | <valeur> %d | <droit>\"];\n", (void*) a, (int) a->valeur);

    // fils gauche s'il y en a
    if (a->fg)
        fprintf(f, "    n%p:gauche:c -> n%p:valeur;\n", (void*) a, (void*) a->fg);

    // fils droit s'il y en a
    if (a->fd)
        fprintf(f, "    n%p:droit:c -> n%p:valeur;\n", (void*) a, (void*) a->fd);

    ecrireArbre(f, a->fg);
    ecrireArbre(f, a->fd);
}

void dessine(FILE *f, Arbre a){
    ecrireDebut(f);
    ecrireArbre(f, a);
    ecrireFin(f);
}

void creePDF ( char * dot , char * pdf , Arbre a ) {
    FILE * out = fopen(dot, "w") ;
    dessine(out, a) ;
    fclose (out) ;

    int len = strlen(dot) + strlen(pdf) + 20;
    //fprintf(stderr, )
    char * cmd = malloc(len) ;
    snprintf (cmd, len, " dot -Tpdf  %s -o %s", dot, pdf) ;
    system(cmd);
    free(cmd);
}

int main(void){

    srand(time(NULL));
    Arbre a = NULL;

    FILE *f = fopen("arbre_exo.dot", "w+");
    if (!f)
        return 1;

    // if (!non_ABR_presque_complet_alea(&a, 77))
    //     fprintf(stderr, "Erreur de construction\n");
    // else 
    //     fprintf(stderr, "construction réussie\n");

    // int* tmp = (int*) malloc(sizeof(Noeud) * 10);

    // if (!tmp)
    //     return 0;

    // for (int i = 0; i< 10; i++){
    //     (*tab)[i] = rand() % 1000;
    // }

    int tmp[] = {5, 3, 1, 10, -1, -1, 11, -1, -1, 4, 2, -1, -1, 6, -1, -1, 9, 12, 15, -1, -1, 13, -1, -1, 14, 51, -1, -1, 30, -1, -1};

    int *p = tmp;
    int **tab = &p;


    if (!construit_quelconque(&a, tab, 31))
        fprintf(stderr, "Erreur de construction\n");
    else{
        fprintf(stderr, "construction réussie\n");
    }

    dessine(f, a);
    creePDF("visualise.dot", "visualise.pdf", a);
    system("evince visualise.pdf &");

    fprintf(stderr, "hauteur : %d\n", hauteur(a));

    fprintf(stderr, "nombre de noeuds : %d\n", nb_noeuds(a));

    fprintf(stderr, "nombre de feuilles : %d\n", nb_feuilles(a));

    fprintf(stderr, "nombre de noeuds internes : %d\n", nb_internes(a));

    detruit_arbre(a);
    fclose(f);
    return 0;
}
