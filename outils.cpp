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

void erosion(string imageUnPath, squareElementStructurant element){
  t_Image *imageUn = new t_Image({0, 0, 0});
  bool statusUn = false;

  loadPgm(imageUnPath, imageUn, statusUn);
  t_Image *result = new t_Image({0, 0, 0});
  result->h = 512;
  result->w = 512;
  for (int i = 0; i < imageUn->h; i++){
    for (int j = 0; j < imageUn->w; j++){
      if(imageUn->im[i][j] == element[1][1] && imageUn->im[i-1][j] == element[0][1] &&
        imageUn->im[i][j-1] == element[1][0] && imageUn->im[i-1][j-1] == element[0][0] &&
        imageUn->im[i][j+1] == element[1][2]){
        result->im[i][j] = 0;
      }
      else{
        result->im[i][j] = 1;
      }
    }
  }
  savePgm("erosion.pgm", result);
  delete imageUn;
  delete result;
}