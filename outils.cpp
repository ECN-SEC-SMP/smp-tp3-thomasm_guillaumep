#include "outils.h"

void difference(string imageUnPath, string imageDeuxPath){
    t_Image* imageUn = new t_Image({0,0,0});
    t_Image* imageDeux = new t_Image({0,0,0});
    bool statusUn = false;
    bool statusDeux = false;

    loadPgm(imageUnPath, imageUn, statusUn);
    loadPgm(imageDeuxPath, imageDeux, statusDeux);
    t_Image *result = new t_Image({0,0,0});
    result->h = 512;
    result->w = 512;
    for(int i = 0; i < imageUn->h; i++){
        for(int j = 0; j < imageUn->w; j++){
            result->im[i][j] = abs(int(imageUn->im[i][j] - imageDeux->im[i][j]));
        }
    }
    savePgm("difference.pgm", result);
    delete imageUn;
    delete imageDeux;
    delete result;
}