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
        temps   = float(ligne["Temps"])

        if morph not in donnees:
            donnees[morph] = {}
        if methode not in donnees[morph]:
            donnees[morph][methode] = {"tailles": [], "visites": [], "temps": []}

        donnees[morph][methode]["tailles"].append(taille)
        donnees[morph][methode]["visites"].append(visites if visites > 0 else 0.001)
        donnees[morph][methode]["temps"].append(temps if temps > 0 else 0.000001)

methodes = ["Naif", "Definition", "Infixe"]
morphologies = list(donnees.keys())

# Figure 1 : Nb visites 
fig1, axes1 = plt.subplots(1, 3, figsize=(18, 5))
fig1.suptitle("Nb noeuds visites selon la morphologie")

for i, methode in enumerate(methodes):
    ax = axes1[i]
    ax.set_title(methode)
    ax.set_xlabel("Taille")
    ax.set_ylabel("Nb noeuds visites")
    ax.set_yscale("log")
    for morph in morphologies:
        if morph not in donnees or methode not in donnees[morph]:
            continue
        d = donnees[morph][methode]
        ax.plot(d["tailles"], d["visites"], marker="o", label=morph)
    ax.legend(fontsize=7)
    ax.grid(True)

fig1.tight_layout()
fig1.savefig("visites_par_methode.png")
plt.close()
print("visites_par_methode.png genere")

# Figure 2 : Temps 
fig2, axes2 = plt.subplots(1, 3, figsize=(18, 5))
fig2.suptitle("Temps d'execution selon la morphologie")

for i, methode in enumerate(methodes):
    ax = axes2[i]
    ax.set_title(methode)
    ax.set_xlabel("Taille")
    ax.set_ylabel("Temps (s)")
    for morph in morphologies:
        if morph not in donnees or methode not in donnees[morph]:
            continue
        d = donnees[morph][methode]
        ax.plot(d["tailles"], d["temps"], marker="o", label=morph)
    ax.legend(fontsize=7)
    ax.grid(True)

fig2.tight_layout()
fig2.savefig("temps_par_methode.png")
plt.close()
print("temps_par_methode.png genere")
