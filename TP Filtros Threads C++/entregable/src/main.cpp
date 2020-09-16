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
	
	//ppm img_target(img1);
	// string img2(argv[6]);
	// ppm imgdos(img2);
	
	ppm img_target(ppm(img.width, img.height));

	cout << "Aplicando filtro" << endl;
	


	struct timespec start, stop;
    double accum;
	clock_gettime(CLOCK_REALTIME, &start);
	
	
	// MULTITHREAD BW
	// ppm *punteroimg = &img;
	// ppm *punterotarget = &img_target;
	// unsigned int nthreads = std::thread::hardware_concurrency();
	// std::thread threads[nthreads];

	// for(unsigned int i = 0 ; i < nthreads; i++)
	// {
	// 	// vthread.push_back(thread(std::ref(blackWhite_mt), std::ref(img_target) ,nthreads ,i));
	// 	threads[i]= std::thread(blackWhite_mt, std::ref(punteroimg), std::ref(punterotarget) , nthreads ,i);
	// }
	
	// for(int i = 0 ; i < nthreads; i++)
	// {	
	// 	threads[i].join();
	// }
	
	// MERGE
	// string rutaimagen("./imgs/cebra.ppm");
	// merge(img, imgdos, 0.7);

	// ZOOM 
	// int n = 3;
	//zoom(img, img_target, n);
	
	// CROP
	// int filaseliminar = 300;
	// int columnaseliminar = 300;	
	// ppm img_target(ppm( img.width - columnaseliminar, img.height - filaseliminar));
	// crop(img, img_target, columnaseliminar, filaseliminar);

	edgeDetection(img, img_target);

	clock_gettime(CLOCK_REALTIME, &stop);
	accum = ( stop.tv_sec - start.tv_sec ) + ( stop.tv_nsec - start.tv_nsec ) * ONE_OVER_BILLION; 
	printf( "Duración del filtrado: %lf s\n", accum);
	
	cout << "Escribiendo imagen" << endl;
	string out = "./out.ppm";
	img_target.write(out);  

	cout << "Listo" << endl;
	return 0;
}