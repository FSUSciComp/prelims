# include <cmath>
# include <cstdlib>
# include <ctime>
# include <iostream>
# include <iomanip>
# include <mpi.h>

using namespace std;

int search ( int a, int b, int c );
int f ( int i );

//****************************************************************************80

int main (int argc, char *argv[] )

//****************************************************************************80
{
/*

	B is a 3x3 matrix
	a is a mx1 vector
	c is a nx1 vector

	B*a = c

*/

//	mpi varaibles
	int id;		//
	int p;		//

	int i;
	int j;
	double wtime = 0.0;


	int m = 3;  // columns
	int n = 3;  //rows

	double B[n][m];
	double a[m];
	double c[i];
	double global_sum_send[n];
	double global_sum_recv[n];	

	//sample matrix

	for ( i = 0; i < n; i++ )
	{
	     for ( j = 0; j < m ; j++ )
		B[i][j] = 10;
	}
	

	//edits to sample matrix
	B[0][0] = 2;
	B[1][0] = 5;
	B[1][2] = 17;

	//sample vector
	for ( i = 0; i < m ; i++ )
		a[i] = 2;


	//filling answer with zeros to initialize
	for (i = 0; i < n ; i++)
	{
		c[i] = 0;
		global_sum_send[i] = 0;
	}

	double product = 0;


	//suppose we have n = processors
	//MPI region
	MPI_Init (&argc, &argv);
	MPI_Comm_rank (MPI_COMM_WORLD, &id);
	MPI_Comm_size (MPI_COMM_WORLD, &p);	

	int row = id;

	for (i = 0; i < m ; i ++)
	{	
		product = product + ( (B[row][i])*(a[i]) );
	}
	
	//c[row] = product;


	//cout <<"----------------------------------"<< endl;
	
	cout << "Row "<< id << " dot product = " << product << endl;

	global_sum_send[row] = c[row] + product;

	//cout <<"----------------------------------"<< endl;


	//Reducing	

	MPI_Allreduce(&global_sum_send, &c, m, MPI_DOUBLE, MPI_SUM,  MPI_COMM_WORLD);

//	Terminate.
//
//	Exiting MPI zone
	MPI_Finalize();

	if(id == 0)
	{
		cout << " c vector " << endl;
		for ( i = 0; i < n ; i++)
		{
			cout << c[i] << endl;
		}		


 		cout << "\n";
 		cout << "MPI_Compute:\n";
		cout << "  Normal end of execution.\n";
		cout << endl;
	}

	return 0;
}




































