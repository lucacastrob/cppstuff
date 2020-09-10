#ifndef FILTERS_H
#define FILTERS_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "ppm.h"
#include <atomic>


// SINGLE-THREAD FILTERS

void blackWhite(ppm& img); //Nos toca
void shades(ppm& img, unsigned char shades); //Nos toca
void merge(ppm& img1, ppm& img2, float alpha); //Nos toca
void zoom(ppm &img, ppm &img_zoomed, int n); //Nos toca
void edgeDetection(ppm &img, ppm &img_target); //Nos toca

void contrast(ppm& img, float contrast);
void brightness(ppm& img, float b, int start, int end);
void frame(ppm& img, pixel color, int x);
void boxBlur(ppm &img);


// MULTI-THREAD FILTERS

#endif