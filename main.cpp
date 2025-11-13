#include "chargesauve.h"
#include "outils.h"
#include "elementStructurant.h"

#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
  bool ok = false;
  unsigned int seuil = 128;
  seuillage("./woman512x512.pgm", seuil, ok);
  difference("./kodie512x512.pgm", "./lena512x512.pgm");
  squareElementStructurant square = {{
                                      {0, 1, 0},
                                      {1, 1, 1},
                                      {0, 1, 0},
}};
  erosion("./spriteErosion.pgm", square);
  return 0;
}