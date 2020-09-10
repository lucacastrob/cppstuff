#include <iostream>
#include "ppm.cpp"
#include <string>
#include <stdlib.h>
#include <math.h>       /* sqrt */
#include <vector>
#include "filters.h"
#include <thread>  
#include <atomic> 
 

#define BLACKWHITE ppm

using namespace std;
void blackWhite(ppm& img)
{
    ppm nuevo;
    for (int ancho = 0 ; ancho <= img.width; ancho++)
    {
        cout << ancho;
        for (int altura = 0 ; altura <= img.height; altura++)
        {
            pixel xd = img.getPixel(altura, ancho);
            int g = (xd.r + xd.g + xd.b) / 3;
            pixel p = pixel(g,g,g);
            
            img.setPixel(ancho, altura, p);
            if(ancho ==  img.width - 1 && altura == img.height - 1)
            {
                cout << "asdas";
                img.write("./out.ppm");
            }
            
            // nuevo = img;

        }
    }
    // nuevo.write("./out.ppm");
}
// COMPLETAR :)