#include "chargesauve.h"        // pour les fonctions de chargement et sauvegarde d'images
#include "outils.h"             // pour les fonctions de traitement d'images
#include "elementStructurant.h" // pour la définition des éléments structurants

#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    bool ok = false;                                       // variable pour vérifier le succès des opérations
    unsigned int seuil = 155;                              // seuil pour le seuillage
    seuillage("./woman512x512.pgm", seuil, ok);            // seuillage de l'image
    difference("./kodie512x512.pgm", "./lena512x512.pgm"); // différence entre deux images

    squareElementStructurant square1 = // élément structurant carré 3x3
        {{
            {0, 1, 0},
            {1, 1, 1},
            {0, 1, 0},
        }};

    dilatation(square1, "./woman512x512_seuillée.pgm", ok); // dilatation avec l'élément structurant square1
    squareElementStructurant square = {{
        // élément structurant pour l'érosion
        {0, 1, 0},
        {1, 1, 1},
        {0, 1, 0},
    }};
    erosion("./spriteErosion.pgm", square); // érosion avec l'élément structurant square

    ouverture("./woman512x512_seuillée.pgm", square1, ok); // ouverture avec l'élément structurant square1
    fermeture("./woman512x512_seuillée.pgm", square1, ok); // fermeture avec l'élément structurant square1

    seuillage("./plane512x512.pgm", seuil, ok);            // seuillage de l'image plane
    ouverture("./plane512x512_seuillée.pgm", square1, ok); // ouverture avec l'élément structurant square1
    fermeture("./plane512x512_seuillée.pgm", square1, ok); // fermeture avec l'élément structurant square1

    return 0; // fin du programme
}