import csv
import matplotlib.pyplot as plt

# donnees[morphologie][methode] = {"tailles": [], "visites": [], "temps": []}
donnees = {}

with open("mesures.csv", newline="") as f:
    lecteur = csv.DictReader(f, delimiter=";")
    for ligne in lecteur:
        morph   = ligne["Morphologie"]
        methode = ligne["Methode"]
        taille  = int(ligne["Taille"])
        visites = float(ligne["Nb_visites"])
        temps   = float(ligne["Temps"]) * 1000  # en millisecondes

        if morph not in donnees:
            donnees[morph] = {}
        if methode not in donnees[morph]:
            donnees[morph][methode] = {"tailles": [], "visites": [], "temps": []}

        donnees[morph][methode]["tailles"].append(taille)
        donnees[morph][methode]["visites"].append(visites)
        donnees[morph][methode]["temps"].append(temps)

methodes    = ["Naif", "Definition", "Infixe"]
morphologies = list(donnees.keys())

for morph in morphologies:

    # Nb visites selon la taille 
    plt.figure()
    plt.title(morph + " - Nb noeuds visites")
    plt.xlabel("Taille")
    plt.ylabel("Nb noeuds visites")

    for methode in methodes:
        if methode not in donnees[morph]:
            continue
        d = donnees[morph][methode]
        plt.plot(d["tailles"], d["visites"], marker="", label=methode)

    import math

    tailles = d["tailles"]  # prends les tailles d'une methode quelconque

    # courbes de référence
    plt.plot(tailles, [t for t in tailles], linestyle="--", color="gray", label="n")
    plt.plot(tailles, [t * math.log2(t) if t > 0 else 0 for t in tailles], linestyle="--", color="red", label="n log n")
    plt.plot(tailles, [t * t / 1000 for t in tailles], linestyle="--", color="purple", label="n² /1000")

    plt.legend()
    plt.grid(True)
    plt.savefig(morph + "_visites.png")
    plt.close()
    print(morph + "_visites.png genere")

    # Temps selon la taille 
    plt.figure()
    plt.title(morph + " - Temps d'execution")
    plt.xlabel("Taille")
    plt.ylabel("Temps moyen (ms)")

    for methode in methodes:
        if methode not in donnees[morph]:
            continue
        d = donnees[morph][methode]
        plt.plot(d["tailles"], d["temps"], marker="", label=methode)

    import math

    tailles = d["tailles"]  # prends les tailles d'une methode quelconque

    # courbes de référence
    plt.plot(tailles, [t for t in tailles], linestyle="--", color="gray", label="n")
    plt.plot(tailles, [t * math.log2(t) if t > 0 else 0 for t in tailles], linestyle="--", color="red", label="n log n")
    plt.plot(tailles, [t * t / 1000 for t in tailles], linestyle="--", color="purple", label="n² /1000")

    plt.legend()
    plt.grid(True)
    plt.savefig(morph + "_temps.png")
    plt.close()
    print(morph + "_temps.png genere")