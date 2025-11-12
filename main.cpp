#include "chargesauve.h"
#include "outils.h"

#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
  bool ok = false;
  unsigned int seuil = 128;
  seuillage("./woman512x512.pgm", seuil, ok);
  difference("./kodie512x512.pgm", "./lena512x512.pgm");
  return 0;
}