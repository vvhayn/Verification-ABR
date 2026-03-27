# ============================================================
#  Makefile — Projet Arbre Binaire de Recherche
# ============================================================

CC      = clang
CFLAGS  = -Wall -Wextra -g -std=c17
TARGET  = programme

# Tous les fichiers objets nécessaires
OBJ     = main.o \
          fonctions_de_test.o \
          genere_arbre_binaire.o \
          est_ABR.o \
		  structure_arbre.o

# ------------------------------------------------------------
# Cible principale : édition des liens
# ------------------------------------------------------------
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) -lm

# ------------------------------------------------------------
# Compilation des fichiers objets avec leurs dépendances
# ------------------------------------------------------------

# main dépend de tous les en-têtes (il utilise tout)
main.o: main.c fonctions_de_test.h genere_arbre_binaire.h est_ABR.h
	$(CC) $(CFLAGS) -c main.c -o main.o

# fonctions_de_test : module de base, pas de dépendance interne
fonctions_de_test.o: fonctions_de_test.c fonctions_de_test.h
	$(CC) $(CFLAGS) -c fonctions_de_test.c -o fonctions_de_test.o

# genere_arbre_binaire dépend de fonctions_de_test
genere_arbre_binaire.o: genere_arbre_binaire.c genere_arbre_binaire.h fonctions_de_test.h
	$(CC) $(CFLAGS) -c genere_arbre_binaire.c -o genere_arbre_binaire.o

# est_ABR dépend de genere_arbre_binaire (et donc transitvement de fonctions_de_test)
est_ABR.o: est_ABR.c est_ABR.h genere_arbre_binaire.h
	$(CC) $(CFLAGS) -c est_ABR.c -o est_ABR.o

structure_arbre.o: structure_arbre.c structure_arbre.h
	$(CC) $(CFLAGS) -c structure_arbre.c -o structure_arbre.o

# ------------------------------------------------------------
# Cibles utilitaires
# ------------------------------------------------------------

# Supprime les fichiers objets et l'exécutable
clean:
	rm -f $(OBJ) $(TARGET) | rm -f *.dot | rm -f visualise.pdf

# Force une recompilation totale
re: clean $(TARGET)

# Ces cibles ne correspondent pas à des fichiers
.PHONY: clean re