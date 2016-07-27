//Author: Juan G. Llanos
//Description: Solution for question 8 in prelim 2012 (spring)
// Implementation of a parallel lower triangular matrix solver
// using OpenMP

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <omp.h>
using namespace std;

void print_array(double *x, const int n){
	cout << '[';
	for (int i = 0; i < n; i++){
		cout << x[i] << ' ';
	}
	cout << ']' << endl;;
}

int main(){
	const int n = 10;
	int threads[] = {1, 2, 4, 8};
	double wall_time = 0;
	double b[n];
	double x[n];
	double A[n][n];

	//initialize matrix and vector with uniform-ish random numbers
	int rand_min = 1;
	int rand_max = 10;
	
	for (int i = 0; i < n; i++){
		b[i] = rand_min + (rand() % (rand_max - rand_min + 1));
		//b[i] = i+1;
		for (int j = 0; j <= i; j++){
			A[i][j] = rand_min + (rand() % (rand_max - rand_min + 1));
		}
	}
	cout << "For an nxn matrix (n = " << n << ")" << endl;
	cout << "# threads, time" << endl;
	for (int t = 0; t < 4; t++){
		omp_set_num_threads(threads[t]);
		cout << omp_get_max_threads();
		wall_time = omp_get_wtime();
		//forward solve
		for (int i = 0; i < n; i++){
			x[i] = b[i];
			double xi = b[i];
			int j;
			#pragma omp parallel shared(A, x) private(j) reduction(- : xi)
			#pragma omp for
			for (j = 0; j < i; j++){
				xi -= A[i][j]*x[j];
			}
			x[i] = xi/A[i][i];
		}
		wall_time = omp_get_wtime() - wall_time;
		cout << ", " << wall_time << endl;
		//print_array(x, n);
	}
	
	
	return 0;
}
