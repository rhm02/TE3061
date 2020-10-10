#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

#define NUM_THREADS 100

int main()
{
    FILE *image, *outputImage, *lecturas;
    image = fopen("sample.bmp","rb");          //Imagen original a transformar
    outputImage = fopen("img2_dd.bmp","wb");    //Imagen transformada
    unsigned char r, g, b, pixel;               //Pixel
    unsigned char* color;
    unsigned char* gris;

    color = (unsigned char*)malloc(927361*3*sizeof(unsigned char));
    gris = (unsigned char*)malloc(927361*3*sizeof(unsigned char));

    for(int i=0; i<54; i++) fputc(fgetc(image), outputImage);   //Copia cabecera a nueva imagen

	for(int i = 0; i < 927361*3; i+=3){                                        //Grises
		*(color + i) = fgetc(image);
		*(color + i+1) = fgetc(image);
		*(color + i+2) = fgetc(image);
	}

    
    
    #pragma omp for 
    //#pragma omp parallel for schedule(guided)
	for(int i = 54; i < 927361*3; i+=3){                                        //Grises
		r = *(color + i);
		g = *(color + i+1);
		b = *(color + i+2);
		unsigned char pixel = 0.21*r + 0.72*g + 0.07*b;
		*(gris+i) = pixel;
		*(gris+i+1) = pixel;
		*(gris+i+2) = pixel;
	}
    for (int i = 54; i < 927361*3; i++)
    {
    	fputc(*(gris+i), outputImage);
    }
    free(color);
    free(gris);
    fclose(image);
    fclose(outputImage);
    return 0;
}
