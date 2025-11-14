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

void difference(string imageUnPath, string imageDeuxPath)
{
  t_Image *imageUn = new t_Image({0, 0, 0});
  t_Image *imageDeux = new t_Image({0, 0, 0});
  bool statusUn = false;
  bool statusDeux = false;

  loadPgm(imageUnPath, imageUn, statusUn);
  loadPgm(imageDeuxPath, imageDeux, statusDeux);
  t_Image *result = new t_Image({0, 0, 0});
  result->h = 512;
  result->w = 512;
  for (int i = 0; i < imageUn->h; i++)
  {
    for (int j = 0; j < imageUn->w; j++)
    {
      result->im[i][j] = abs(int(imageUn->im[i][j] - imageDeux->im[i][j]));
    }
  }
  savePgm("difference.pgm", result);
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