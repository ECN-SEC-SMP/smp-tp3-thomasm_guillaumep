#include "outils.h"

void seuillage(string NomImage, unsigned int &seuil, bool &okOut)
{
  bool okIn = false;
  t_Image *Image = new t_Image({0, 0, 0});
  loadPgm(NomImage, Image, okIn);
  if (okIn)
  {
    // okIn = false;
    for (int i = 0; i < Image->w; i++)
    {
      for (int j = 0; j < Image->h; j++)
      {
        if (Image->im[i][j] < seuil)
        {
          Image->im[i][j] = 0;
        }
        else
        {
          Image->im[i][j] = 255;
        }
      }
    }
    size_t pos = NomImage.find_last_of('.');
    NomImage.insert(pos, "_seuillée");
    savePgm(NomImage, Image);
    okOut = true;
  }
  else
  {
    okOut = false;
  }
  delete Image;
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

// Fonction erosion prennant en paramètre le chemin vers une image ainsi qu'un élément structurant
void erosion(string imageUnPath, squareElementStructurant element){
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
  for (int i = 0; i < imageUn->h; i++){
    for (int j = 0; j < imageUn->w; j++){

      // booléen pour indiquer si l'élément structurant match avec les pixels
      bool okOut = true;

      // On parcours les pixels de l'élément structurant
      for(int k = 2; k >= 0; k--){
        for(int l = 2; l >= 0; l--){
          // Si on est sur les bords de l'image, on ignore
		  if(i-k <= 0 || j-l <= 0 || i+k > imageUn->h || j+l > imageUn->w){
			okOut = false;
			break;
		  }
		  // Si le pixel de l'image est blanc
		  if(imageUn->im[i+k-1][j+l-1] == 255){
			// Si le pixel de l'élément structurant est noir
			if(element[k][l] == 1){
				// Il y a différence
				okOut = false;
			}
		  }
        }
      }
	  // Si il n'y a pas de différence on laisse le pixel noir
      if(okOut){
        result->im[i][j] = 0;
      }
	  // Sinon on le change en pixel blanc
      else{
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