#include "outils.h"

// fonction de seuillage d'une image
void seuillage(string NomImage, unsigned int &seuil, bool &okOut)
{
  bool okIn = false;                       // booléean pour savoir si l'image sera bien chargé dans la structure
  t_Image *Image = new t_Image({0, 0, 0}); // structure de l'image qui sera chargé
  loadPgm(NomImage, Image, okIn);          // chargement de l'image dans la structure
  if (okIn)                                // si l'image est bien chargé
  {
    // okIn = false;
    for (int i = 0; i < Image->w; i++) // parcours de l'image
    {
      for (int j = 0; j < Image->h; j++)
      {
        if (Image->im[i][j] < seuil) // seuillage
        {
          Image->im[i][j] = 0; // noir
        }
        else
        {
          Image->im[i][j] = 255; // blanc
        }
      }
    }
    // nouveau nom de la nouvelle image pour l'enregistrement
    size_t pos = NomImage.find_last_of('.');
    NomImage.insert(pos, "_seuillée");
    savePgm(NomImage, Image);
    okOut = true; // true pour dire que tout s'est bien passé
  }
  else // si problème de chargement
  {
    okOut = false; // retour du booléen false
  }
  delete Image; // libération de la mémoire
}

// Fonction difference prennant en paramètre le chemin des deux images
void difference(string imageUnPath, string imageDeuxPath)
{
  // Instensiation des pointeurs vers les deux images
  t_Image *imageUn = new t_Image({0, 0, 0});
  t_Image *imageDeux = new t_Image({0, 0, 0});

  // Booléen pour représenter le chargement de l'image
  bool statusUn = false;
  bool statusDeux = false;

  // Chargement des deux images
  loadPgm(imageUnPath, imageUn, statusUn);
  loadPgm(imageDeuxPath, imageDeux, statusDeux);

  // Instensiation du pointeur vers le résultat
  t_Image *result = new t_Image({0, 0, 0});

  // On définit la résolution de l'image
  result->h = 512;
  result->w = 512;

  // On parcours les pixels des deux images
  for (int i = 0; i < imageUn->h; i++)
  {
    for (int j = 0; j < imageUn->w; j++)
    {
      // Dans le résultat, on prend la valeur absolue de la différence des deux images
      result->im[i][j] = abs(int(imageUn->im[i][j] - imageDeux->im[i][j]));
    }
  }
  // On sauvegarde le résultat de l'image
  savePgm("difference.pgm", result);

  // On supprime les pointeurs des deux images et du résultat
  delete imageUn;
  delete imageDeux;
  delete result;
}

// fonction permettant de faire la dilation d'une image à partir d'une image en noir et blanc (seuillage/différence)
void dilatation(squareElementStructurant &elementStructurant, string NomImage, bool &okOut)
{
  okOut = false;
  t_Image *Image = new t_Image({0, 0, 0}); // structure de l'image qui sera chargé
  bool okIn = false;                       // booléean pour savoir si l'image sera bien chargé dans la structure
  loadPgm(NomImage, Image, okIn);          // chargement de l'image dans la structure
  if (!okIn)                               // si problème de chargement
  {
    okOut = false; // retour du booléen false
    delete Image;  // libération de la mémoire
    return;        // on sort de la fonction
  }
  // copie de l'image originale dans une temporaire pour que le les modifs n'impactent pas l'analyse de l'image originale'
  t_Image *ImageOut = new t_Image({Image->w, Image->h, {0}});
  // on remplie la nouvelle structure de sortie
  for (int i = 0; i < Image->h; i++)
  {
    for (int j = 0; j < Image->w; j++)
    {
      ImageOut->im[i][j] = Image->im[i][j];
    }
  }
  // traitement
  // on parcourt toute l'image
  for (int i = 0; i < Image->h; i++)
  {
    for (int j = 0; j < Image->w; j++)
    {
      // si le pixel est blanc alors on le dilate en suivant l'élément structurant
      if (Image->im[i][j] == 255)
      {
        // on parcourt tout l'élément structurant (attention boucle for en négatif pour être de bien avoir tous les pixels)
        for (int m = -WIDTH / 2; m <= WIDTH / 2; m++)
        {
          for (int n = -WIDTH / 2; n <= WIDTH / 2; n++)
          {
            if (elementStructurant[m + WIDTH / 2][n + WIDTH / 2]) // si c'est true dans l'élement structurant
            {
              // calcul de la position actuelle
              int x = i + m;
              int y = j + n;
              if (x >= 0 && x < Image->h && y >= 0 && y < Image->w) // et si c'est bien dans les dimensions de l'image
              {
                ImageOut->im[x][y] = 255; // on met le pixel en blanc
              }
            }
          }
        }
      }
    }
  }
  // nouveau nom de la nouvelle image pour l'enregistrement
  size_t pos = NomImage.find_last_of('.');
  NomImage.insert(pos, "_dilaté");
  savePgm(NomImage, ImageOut);
  okOut = true; // true pour dire que tout s'est bien passé
  delete Image; // libération de la mémoire
  delete ImageOut;
}

// Fonction erosion prennant en paramètre le chemin vers une image ainsi qu'un élément structurant
void erosion(string imageUnPath, squareElementStructurant element)
{
  // Création du pointeur de l'image
  t_Image *imageUn = new t_Image({0, 0, 0});

  // Status du chargement de l'image
  bool statusUn = false;

  // Chargement de l'image
  loadPgm(imageUnPath, imageUn, statusUn);

  // Création du pointeur du résultat de l'image
  t_Image *result = new t_Image({0, 0, 0});

  // Définition de la résolution de l'image
  result->h = 512;
  result->w = 512;

  // On parcours tout les pixels de l'image sur laquelle on veut faire l'érosion
  for (int i = 0; i < imageUn->h; i++)
  {
    for (int j = 0; j < imageUn->w; j++)
    {

      // booléen pour indiquer si l'élément structurant match avec les pixels
      bool okOut = true;

      // On parcours les pixels de l'élément structurant
      for (int k = 2; k >= 0; k--)
      {
        for (int l = 2; l >= 0; l--)
        {
          // Si on est sur les bords de l'image, on ignore
          if (i - k <= 0 || j - l <= 0 || i + k > imageUn->h || j + l > imageUn->w)
          {
            okOut = false;
            break;
          }
          // Si le pixel de l'image est blanc
          if (imageUn->im[i + k - 1][j + l - 1] == 255)
          {
            // Si le pixel de l'élément structurant est noir
            if (element[k][l] == 1)
            {
              // Il y a différence
              okOut = false;
            }
          }
        }
      }
      // Si il n'y a pas de différence on laisse le pixel noir
      if (okOut)
      {
        result->im[i][j] = 0;
      }
      // Sinon on le change en pixel blanc
      else
      {
        result->im[i][j] = 255;
      }
    }
  }

  // On sauvegarde l'image
  savePgm("erosionEssai.pgm", result);

  // On supprime les pointeurs
  delete imageUn;
  delete result;
}

// érosion suivi de dilatation
void ouverture(string NomImage, squareElementStructurant element, bool &okOut)
{
  erosion(NomImage, element);
  dilatation(element, NomImage, okOut);
}

// dilatation suivi d'érosion
void fermeture(string NomImage, squareElementStructurant element, bool &okOut)
{
  dilatation(element, NomImage, okOut);
  erosion(NomImage, element);
}