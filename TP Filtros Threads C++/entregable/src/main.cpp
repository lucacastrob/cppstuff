#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include "filters.h"
#include <thread>
#define ONE_OVER_BILLION 1E-9



int main(int argc , char* argv[]){
	
	// Pasamos 0 en caso de no utilizar p2 o  "" en img2
	
	if(string(argv[1]) == "-help")
	{
		cout << "Uso: ./tp <filtro> <nthreads> <p1> <p2> <img1> <img2>" << endl;
		return 0; 
	}

	string img1(argv[5]);
	ppm img(img1);
	
	int filaseliminar = 300;
	int columnaseliminar = 300;
	ppm img_target((ppm(img.width*n, img.height*n)));
	ppm img_target(ppm( img.width - columnaseliminar, img.height - filaseliminar));

	// string img2(argv[6]);
	// ppm imgdos(img2);

	cout << "Aplicando filtro" << endl;
	
	struct timespec start, stop;
    double accum;
	clock_gettime(CLOCK_REALTIME, &start);
	
	// string rutaimagen("./imgs/cebra.ppm");
	// merge(img, imgdos, 0.7);

	crop(img, img_target, columnaseliminar, filaseliminar);

	clock_gettime(CLOCK_REALTIME, &stop);
	accum = ( stop.tv_sec - start.tv_sec ) + ( stop.tv_nsec - start.tv_nsec ) * ONE_OVER_BILLION; 
	printf( "Duración del filtrado: %lf s\n", accum);
	
	cout << "Escribiendo imagen" << endl;
	string out = "./out.ppm";
	img_target.write(out);  

	cout << "Listo" << endl;
	return 0;
}