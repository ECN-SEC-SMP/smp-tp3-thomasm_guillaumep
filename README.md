# SMP – TP3 – Erosion-dilatation

## 1) Introduction
Objectif: Réaliser un algorithme de dilatation et d'érosion pour faire du traitement d'image au format PGM.

---

## 2) Fichiers utilisés
- `chargesauve.h/.cpp` : Pour charger ou sauvegarder une image au format .PGM.
- `outils.h/.cpp` : Contient les méthodes de seuillage, différence, dilatation et erosion.
- `main.cpp` : Jeux d'essais des différentes méthodes.
- `elementStructurant.h` : Définition de la structure de l'élément structurant pour la dilatation et l'érosion.

---

## 3) Fonctions et validations

### A. `seuillage(string NomImage, unsigned int &seuil, bool &okOut) → void`
- **Spécification** : Remplace les pixels d'un niveau de gris inférieur au seuil.
- **Principe** : Si le pixel est inférieur au seuil, celui-ci est remplacé par un pixel noir, sinon par un pixel blanc.
- **Essais** : 

[image avant seuillage]
[image après seuillage]

### B. `difference(string imageUnPath, string imageDeuxPath) → void`
- **Spécification** : Effectue la différence entre deux images.
- **Principe** : Prend chaque pixel des deux images et calcul la valeur absolue de la différence des valeurs du pixel des deux images.
- **Essais** :

[image avant difference]
[image après difference]

### C. `dilatation(squareElementStructurant &elementStructurant, string NomImage, bool &okOut) → void`
- **Spécification** : Permet d'agrendir le pixel d'une image en fonction de l'élément structurant.
- **Principe** : Analyse chaque pixel d'une image et fait correspondre la forme de l'élément structurant en ajoutant des pixels blancs.
- **Essais** :

[image avant dilatation]
[image après dilatation]

### D. `erosion(string imageUnPath, squareElementStructurant element) → void`
- **Spécification** : Permet de réduire les objets dans une image en supprimant les pixels sur leurs contours.
- **Principe** : Vérifie chaque pixel de l'image et vérifie si ils correspondent à l'élément structurant. Si les pixels ne correspondent pas à ceux de l'élément structurant, le pixel est remplacé par un pixel blanc.
- **Essais** :

[image avant erosion]
[image après erosion]

---

## 4) Conclusion
Les fonctions de **seuillage**, **difference**, **dilatation** et **erosion** fonctionnent selon l'énoncé.
