#include "chargesauve.h"
#include "outils.h"

#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
  bool ok = false;
  unsigned int seuil = 155;
  seuillage("./woman512x512.pgm", seuil, ok);
  difference("./kodie512x512.pgm", "./lena512x512.pgm");

  squareElementStructurant square1 =
      {{
          {0, 1, 0},
          {1, 1, 1},
          {0, 1, 0},
      }};

  dilatation(square1, "./woman512x512_seuillée.pgm", ok);
  return 0;
}