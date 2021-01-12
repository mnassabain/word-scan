# Word Scan

## About 

Le but de ce programme est la génération d'un **dictionnaire** depuis un fichier texte. Le dictionnaire aura la forme d'un **arbre binaire de recherche (ABR)**.

Extrait du sujet

> L'arbre binaire de recherche résultant contiendra l'intégralité des mots du texte parcouru. Chaque mot représente une clé de l'arbre. De plus, nous associons à chacun de ces noeuds l'ensemble de positions des occurrences du mot dans le texte. Par convention, si un même mot apparait plusieurs fois au sein d'une même phrase, il est sauvegardé qu'une fois dans l'ensemble des positions. La recherche des (co)occurrences de plusieurs mots consiste à faire l'intersection des ensembles de positions associés à chacun des mots dans l'arbre binaire de recherche. Ces deux structures de données sont crées en parcourant séquentiellement le texte, phrase par phrase et mot par mot.

## Utilisation

```
# Compilation
make

# Lancer programme
./analyser input.file

# Options:
-a : Affiche une aide pour l'utilisation
-h : Affiche la hauteur de l'ABR
-p : Affiche la profondeur moyenne des noeuds de l'arbre
-n : Affiche le nombre de noeuds de l'arbre
-e : Teste si l'arbre est bien équilibré
-u : Passage en mode utf-8 pour raiter les accents
-i : Lance le programme en mode interactif
-t : Lance un jeu de tests 

Les options -i et -t peuvent être utilisées simultanement afin de lancer un jeu de tests en mode interactif.
```