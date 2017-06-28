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
	c is a 1xn vector

	B*a = c

*/

//	mpi varaibles
	int id;		//
	int p;		//
	MPI_Status status;

	int i;
	int j;
	double wtime = 0.0;


	int m = 3;  // columns
	int n = 3;  //rows

	double B[n][m];
	double a[m];
	double c[i];
	double send_product = 0;	

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
	
	//cout <<"----------------------------------"<< endl;
	
	cout << "Row "<< id << " dot product = " << product << endl;

	//cout <<"----------------------------------"<< endl;

	if(id != 0)
	{

		send_product = product;
		MPI_Send(&send_product, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);		

	}

	if(id == 0)
	{

		c[id] = product;

		for(i = 1; i < p ; i++)
		{
			MPI_Recv(&send_product, 1, MPI_DOUBLE, i , 0, MPI_COMM_WORLD, &status);
			c[i] = send_product;
		}
	}

//	Terminate.
//
//	Exiting MPI zone
	MPI_Finalize();

	if(id == 0)
	{
		cout << "c vector " << endl;
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




































