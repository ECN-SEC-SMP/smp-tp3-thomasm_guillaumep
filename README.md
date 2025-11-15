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

![image](resultat/seuillageAvant.pgm)
![image](resultat/seuillageResult.pgm)

### B. `difference(string imageUnPath, string imageDeuxPath) → void`
- **Spécification** : Effectue la différence entre deux images.
- **Principe** : Prend chaque pixel des deux images et calcul la valeur absolue de la différence des valeurs du pixel des deux images.
- **Essais** :

![image](resultat/imageUnDiff.pgm)
![image](resultat/imageDeuxDiff.pgm)
![image](resultat/differenceResult.pgm)

### C. `dilatation(squareElementStructurant &elementStructurant, string NomImage, bool &okOut) → void`
- **Spécification** : Permet d'agrendir le pixel d'une image en fonction de l'élément structurant.
- **Principe** : Analyse chaque pixel d'une image et fait correspondre la forme de l'élément structurant en ajoutant des pixels blancs.
- **Essais** :

![image](resultat/seuillageResult.pgm)
![image](resultat/dilatationResult.pgm)

### D. `erosion(string imageUnPath, squareElementStructurant element) → void`
- **Spécification** : Permet de réduire les objets dans une image en supprimant les pixels sur leurs contours.
- **Principe** : Vérifie chaque pixel de l'image et vérifie si ils correspondent à l'élément structurant. Si les pixels ne correspondent pas à ceux de l'élément structurant, le pixel est remplacé par un pixel blanc.
- **Essais** :

![image](resultat/spriteErosion.pgm)
![image](resultat/erosionResult.pgm)

---

## 4) Conclusion
Les fonctions de **seuillage**, **difference**, **dilatation** et **erosion** fonctionnent selon l'énoncé.
