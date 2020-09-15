#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>       /* sqrt */
#include <vector>
#include "filters.h"
#include <thread>  
#include <atomic>  

using namespace std;

void blackWhite(ppm& img)
{
    for (int ancho = 0 ; ancho < img.width; ancho++)
    {
        for (int altura = 0 ; altura < img.height; altura++)
        {
            short int r = img.getPixel(altura, ancho).r;
            short int g = img.getPixel(altura, ancho).g;
            short int b = img.getPixel(altura, ancho).b;

            int a = (r + g + b) / 3;
            
            img.setPixel(altura, ancho, pixel(a,a,a));
            
        }
    }
}

void shades(ppm& img, unsigned char n)
{
    for (int ancho = 0 ; ancho < img.width; ancho++)
    {
        for (int altura = 0 ; altura < img.height; altura++)
        {
            short int r = img.getPixel(altura, ancho).r;
            short int g = img.getPixel(altura, ancho).g;
            short int b = img.getPixel(altura, ancho).b;

            int rango = 255 / (n - 1);
            int promedio = (r + g + b) / 3;

            int a = (promedio/rango) * rango;
            
            img.setPixel(altura, ancho, pixel(a,a,a));
        }
    }
}

void merge(ppm& img1, ppm& img2, float p1)
{
    for (int ancho = 0 ; ancho < img1.width; ancho++)
    {
        for (int altura = 0 ; altura < img1.height; altura++)
        {
            short int r1 = img1.getPixel(altura, ancho).r;
            short int g1 = img1.getPixel(altura, ancho).g;
            short int b1 = img1.getPixel(altura, ancho).b;

            short int r2 = img2.getPixel(altura, ancho).r;
            short int g2 = img2.getPixel(altura, ancho).g;
            short int b2 = img2.getPixel(altura, ancho).b;

            float p2 = 1 - p1;
            
            img1.setPixel(altura, ancho, pixel(r1 * p1 + r2 * p2,g1 *p1 + g2 * p2 , b1 * p1 + b2 * p2));
        }
    }
}