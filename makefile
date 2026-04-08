# ============================================================
#  Makefile — Projet Arbre Binaire de Recherche
# ============================================================

CC      = clang
CFLAGS  = -Wall -Wextra -g -std=gnu17
TARGET  = programme

# Tous les fichiers objets nécessaires
OBJ     = main.o \
          genere_arbre_binaire.o \
          est_ABR.o \


# ------------------------------------------------------------
# Cible principale : édition des liens
# ------------------------------------------------------------
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# ------------------------------------------------------------
# Compilation des fichiers objets avec leurs dépendances
# ------------------------------------------------------------

# main dépend de tous les en-têtes (il utilise tout)
main.o: main.c genere_arbre_binaire.h est_ABR.h # fonctions_de_test.h
	$(CC) $(CFLAGS) -c main.c -o main.o

# genere_arbre_binaire dépend de fonctions_de_test
genere_arbre_binaire.o: genere_arbre_binaire.c genere_arbre_binaire.h fonctions_de_test.h
	$(CC) $(CFLAGS) -c genere_arbre_binaire.c -o genere_arbre_binaire.o

# est_ABR dépend de genere_arbre_binaire (et donc transitvement de fonctions_de_test)
est_ABR.o: est_ABR.c est_ABR.h genere_arbre_binaire.h
	$(CC) $(CFLAGS) -c est_ABR.c -o est_ABR.o

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