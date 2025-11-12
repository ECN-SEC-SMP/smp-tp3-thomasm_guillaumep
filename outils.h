#pragma once

#include <string>
#include <cmath>
using namespace std;

#include "image.h"
#include "chargesauve.h"
#include "elementStructurant.h"

void seuillage(string NomImage, unsigned int &seuil, bool &okOut);
void difference(string imageUnPath, string imageDeuxPath);

void dilatation(squareElementStructurant &elementStructurant, string NomImage, bool &okOut);