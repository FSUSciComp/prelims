//Seth Boren
//Scientific Programming
//Assignment 1
//Integration of sin(x) function for 0 to PI using Trapezoidal and Simpson rules
//9-3-2016
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <stdio.h>

#include <mpi.h>


using namespace std;

//Definition of function f(x)
double f(double x)
{
	double fOutput = x + (5 * x * x) - (0.5 * x * x * x) ;
	return fOutput;    
}




int main(int argc, char *argv[]) 
{
	//Defining the parameters
	const double PI = 3.141592653589793238462643383279502884;
  	double a;
  	double b;
  
	//mpi variables
	int id;
	int p;
	double size = 10;
	double swap;
	double local_sum;
	double wtime = 0.0;
	double Area_sum;

	int tally;
       	MPI_Status status;

	a = 0;
	b = 10;

	int rank,length;
	char name[BUFSIZ];
	
  	
	//MPI region
 	MPI_Init (&argc, &argv);
  	MPI_Comm_rank (MPI_COMM_WORLD, &id);
  	MPI_Comm_size (MPI_COMM_WORLD, &p);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);	
	MPI_Get_processor_name(name,&length);


  	int offset = ( size / p);
  	a = (id*offset);
  	b = (id+1)*(offset);

	///////////// Sending
/*
	if (id == p-1)
	{
		
		swap = f(a);
		MPI_Send(&swap, offset, MPI_DOUBLE, id-1, 0, MPI_COMM_WORLD);

		double aa = (id*offset);
		local_sum = ( f(a) + f(aa) ) / 2; 

		//cout << "Processor " << tally << " calculated area = " << local_sum << endl;	 
	}

	else if (id == 0)
	{
		
		MPI_Recv(&swap, offset, MPI_DOUBLE, id + 1, 0, MPI_COMM_WORLD, &status);
		
		local_sum = (f(a) + swap) / 2; 	
		//cout << "Processor " << tally << " calculated area = " << local_sum << endl;	 
	}

	else 
	{
		
		swap = f(a);  
		MPI_Send(&swap, offset, MPI_DOUBLE, id-1, 0, MPI_COMM_WORLD);   
		MPI_Recv(&swap, offset, MPI_DOUBLE, id + 1, 0, MPI_COMM_WORLD, &status);
		
		local_sum = (f(a) + swap) / 2;   
		//cout << "Processor " << tally << " calculated area = " << local_sum << endl;	    		
	}

*/		
	
    	if (rank <= p-1 && rank != 0)
    	{
        	swap = f(a);
        	MPI_Send(&swap, offset, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD);
		
		if (rank == p-1)
		{
        		double aa = (id*offset);
        		local_sum = ( f(a) + f(aa) ) / 2; 
		}
    	}
    
	if(rank != p-1)
    	{
        	swap = f(a);  

        	MPI_Recv(&swap, offset, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD, &status);
        
        	local_sum = (f(a) + swap) / 2;
                  
    	}

  	double global_sum;

	//Reducing
	MPI_Reduce(&local_sum, &global_sum, 1 , MPI_DOUBLE, MPI_SUM, 0 , MPI_COMM_WORLD);

	cout << " Area found in processor " << rank << " = "<< local_sum << endl;

  	//Terminate.

  	//Exiting MPI zone
  
  	MPI_Finalize();

  	//Trapezoidal rule Output
	
	if (rank == 0) 
	{
		cout << endl << " Trapezoidal Rule Total Area = "<< global_sum << endl;
	}


  	return 0;

}



