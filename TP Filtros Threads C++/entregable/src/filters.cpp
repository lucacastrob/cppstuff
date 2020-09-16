#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>       /* sqrt */
#include <vector>
#include "filters.h"
#include <thread>  
#include <atomic>  

using namespace std;


void blackWhite_mt(ppm* img, ppm* img_target, unsigned int nthreads, unsigned int thread)
{

    int porcionw = (img->width/(nthreads));
    int porcionh = (img->height/(nthreads));
    int iniciox = porcionw*thread;
    int inicioy = porcionh*thread;

    for (int x =  iniciox; x <  img->width ; x++)
    {
        for (int y =  inicioy ; y < img->height; y++)    
        {
            short int r = img->getPixel(y, x).r;
            short int g = img->getPixel(y, x).g;
            short int b = img->getPixel(y, x).b;

            int a = (r + g + b) / 3;
            
            img_target->setPixel(y, x, pixel(a,a,a));
        }
    }
}

void blackWhite(ppm& img)
{
    int ancho = 0;
    int altura = 0;
    
    for (ancho; ancho < img.width; ancho++)
    {
        for (altura; altura < img.height; altura++)
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

void edgeDetection(ppm& img, ppm& img_target)
{
    int filas = 0;
    int aux0 = 0;
    int aux1 = 0;
    int res, suma, sumaTraspuesta;
    int color;

    // Imagen motor 640 ancho, 480 altura
    
    blackWhite(img);
    boxBlur(img);
    
    short int pixeles[img.height][img.width];
    short int matriz[3][3] = {{1,0,-1},{30,0,-30},{1,0,-1}};
    short int matriztraspuesta[3][3] = {{1,30,1},{0,0,0},{-1,-30,-1}};
    short int matrizResultado[3][3];
    short int matrizResultadoTraspuesta[3][3];
    short int matrizSuma[img.height-2][img.width-2];
    short int matrizSumaTraspuesta[img.height-2][img.width-2];

    
    //Creamos matriz con todos los pixeles con filtro bw
    
    for(int y = 0; y < img.height; y++) // Recorre filas, 479 es la altura en motor
    {
        for(int x = 0; x < img.width; x++) // Recorre columnas, 640 es la altura en motor
        {
            short int r1 = img.getPixel(y, x).r; //Agarramos el red porque pasamos filtro y son los 3 canales iguales
            pixeles[y][x]= r1; //Append to matriz pixeles  
        }
    }
    
    //Recorremos matriz 
    for(int y = 0; y < img.height - 2; y++) // Recorre filas, 479 es la altura en motor
    {
        for (int x = 0; x < img.width - 2; x++) // Recorre columnas, 640 es la altura en motor
        {
                for(int y1= 0; y1 <= 2; y1++) // Opera con la matriz de resultados, hace las filas
                {
                    for(int x1 = 0; x1 <= 2; x1++) // Opera con la matriz de resultados, hace las columnas
                    {
                        matrizResultado[y1][x1] = pixeles[y+y1][x+x1] * matriz[y1][x1];
                        suma += matrizResultado[y1][x1];

                        matrizResultadoTraspuesta[y1][x1] = pixeles[y+y1][x+x1] * matriztraspuesta[y1][x1];
                        sumaTraspuesta += matrizResultadoTraspuesta[y1][x1];
                    }
                }
                suma = suma/9;
                sumaTraspuesta = sumaTraspuesta/9;
                color = sqrt(pow(suma,2) + pow(sumaTraspuesta,2));
                color = (color > 255) ? 255 : (color < 0) ? 0 : color;
                img_target.setPixel(y, x, pixel(color, color, color));
        }
    }
 

}

void crop(ppm& img, ppm& img_target, int col, int filas)
{
    for(int y = filas; y < img.height; y++)
    {
        for(int x = col; x < img.width; x++)
        {
            short int r1 = img.getPixel(y, x).r;
            short int g1 = img.getPixel(y, x).g;
            short int b1 = img.getPixel(y, x).b;

            img_target.setPixel(y - filas, x - col, pixel(r1,g1,b1));
        }        
    }

}

void zoom(ppm& img, ppm& img_zoomed, int n)
{
    for(int y = 0; y < img.height; y++)
    {
        for(int x = 0; x < img.width; x++)
        {
            short int r1 = img.getPixel(y, x).r;
            short int g1 = img.getPixel(y, x).g;
            short int b1 = img.getPixel(y, x).b; 
            
            for (int y1 = 0; y1 < n; y1++)
            {
                for(int x1 = 0; x1 < n; x1++)
                {
                    img_zoomed.setPixel((y*n + y1), (x*n + x1), pixel(r1,g1,b1));
                }
            }
        }
    }
}

void boxBlur(ppm &img) {
	ppm new_image = ppm(img.width - 2, img.height - 2);
	for (size_t i = 1; i < img.height - 1; i++)
	{
		for (size_t j = 1; j < img.width - 1; j++)
		{
			pixel p_final = pixel();
			pixel p0 = img.getPixel(i - 1, j - 1);
			pixel p1 = img.getPixel(i - 1, j);
			pixel p2 = img.getPixel(i - 1, j + 1);
			pixel p3 = img.getPixel(i, j - 1);
			pixel p4 = img.getPixel(i, j);
			pixel p5 = img.getPixel(i, j + 1);
			// movy, movx
			pixel p6 = img.getPixel(i + 1, j - 1);
			pixel p7 = img.getPixel(i + 1, j);
			pixel p8 = img.getPixel(i + 1, j + 1);
			p_final.r = (p0.r + p1.r + p2.r + p3.r + p4.r + p5.r + p6.r + p7.r + p8.r) / 9;
			p_final.g = (p0.g + p1.g + p2.g + p3.g + p4.g + p5.g + p6.g + p7.g + p8.g) / 9;
			p_final.b = (p0.b + p1.b + p2.b + p3.b + p4.b + p5.b + p6.b + p7.b + p8.b) / 9;

			p_final.truncate();
			new_image.setPixel(i - 1, j - 1, p_final);
		}
	}
	img = new_image;
};
