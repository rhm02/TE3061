#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 10

int main(int argc, char const *argv[]) {
	FILE* MatrixFile;
	MatrixFile = fopen("mulmetodo.txt","w");
	int n=1000;
	float mat[n][n];
	float c[n][n];
	double t1,t2,tiempo;
	t1 = omp_get_wtime();

	for (int i = 0; i < n; i++) {
	    for (int j = 0; j < n; j++) {
	      mat[i][j] = j;
	    }
	}

	// //Metodo unrolled and jammed
	// for (int i = 0; i < n; i+=2) {
	//     for (int j = 0; j < n; j++) {
	//       c[i][j]=0;
	//       c[i+1][j]=0;
	//       for (int k = 0; k < n; k++){
	//       	c[i][j] = c[i][j] + mat[i][k]*mat[k][j];
	//       	c[i+1][j] = c[i+1][j] + mat[i+1][k]*mat[k][j];
	//       }
	//     }
	// }

	//Metodo unrolled
	for (int i = 0; i < n; i+=2) {
	    for (int j = 0; j < n; j++) {
	      c[i][j]=0;
	      for (int k = 0; k < n; k++){
	      	c[i][j] = c[i][j] + mat[i][k]*mat[k][j];
	      }
	    }
	    for (int j = 0; j < n; j++) {
	      c[i+1][j]=0;
	      for (int k = 0; k < n; k++){
	      	c[i+1][j] = c[i+1][j] + mat[i+1][k]*mat[k][j];
	      }
	    }
	}

	t2 = omp_get_wtime();
	tiempo = t2-t1;
	printf("Tomo: %lf segundos\n", tiempo);

	for (int i = 0; i < n; i++) {
	    for (int j = 0; j < n; j++) {
	    	fprintf(MatrixFile, "%f\t", c[i][j]);
	    }
	}
	fclose(MatrixFile);
}
