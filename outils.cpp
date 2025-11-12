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

void dilatation(squareElementStructurant &elementStructurant, string NomImage, bool &okOut)
{
  okOut = false;
  t_Image *Image = new t_Image({0, 0, 0});
  bool okIn = false;
  loadPgm(NomImage, Image, okIn);
  if (!okIn)
  {
    okOut = false;
    delete Image;
    return;
  }
  t_Image *original = new t_Image({Image->w, Image->h, {0}});
  t_Image *temp = new t_Image({Image->w, Image->h, {0}});
  // Copy original image to preserve initial state during dilation
  for (int i = 0; i < Image->h; i++)
  {
    for (int j = 0; j < Image->w; j++)
    {
      original->im[i][j] = Image->im[i][j];
      temp->im[i][j] = Image->im[i][j];
    }
  }
  for (int i = 0; i < Image->h; i++)
  {
    for (int j = 0; j < Image->w; j++)
    {
      if (original->im[i][j] == 255)
      {
        for (int m = -WIDTH / 2; m <= WIDTH / 2; m++)
        {
          for (int n = -WIDTH / 2; n <= WIDTH / 2; n++)
          {
            if (elementStructurant[m + WIDTH / 2][n + WIDTH / 2])
            {
              int x = i + m;
              int y = j + n;
              if (x >= 0 && x < Image->h && y >= 0 && y < Image->w)
              {
                temp->im[x][y] = 255;
              }
            }
          }
        }
      }
    }
  }
  size_t pos = NomImage.find_last_of('.');
  NomImage.insert(pos, "_dilaté");
  savePgm(NomImage, temp);
  okOut = true;
  delete original;
  delete temp;
}