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