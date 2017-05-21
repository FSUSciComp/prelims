//----------------------------------molecule.cpp-------------------------
/*This is the cpp file which implement the molecular dynamic algorithm
*/
# include <iostream>
# include <iomanip>
# include <ctime>
# include <cmath>
# include <mpi.h> // added by Chaolun Wang at 01/20/2017
//IMPORTANT! be sure to distribute the data to the workers! EACH WORKER MAY ONLY GET THE DATA NEEDED
using namespace std;

struct cell {
  int host[2];
  int guest[2];
};

int main ( int argc, char *argv[]  );
double energy ( const cell &A );                                //calculate energy of a cell
double sequential(double &time);								//calculate energy using sequential code
double e(double i, double j);                                   //energy function

//****************************************************************************

int main ( int argc, char *argv[]  )

{
	

  double sumtotal;                                           
  double sumprocess=0.0;
//initialize MPI
  MPI::Init ( argc, argv );

  double wtime = MPI::Wtime ( );
  int p = MPI::COMM_WORLD.Get_size (  );                     //  Get the number of processes.
//
//  Determine this processes's rank.
//
  int id = MPI::COMM_WORLD.Get_rank ( );

  MPI::Request request;                              //declear the mpi request, used for check the buffer of Ireceive


  int n=8, left, right, pass=0;
  int buffer[2];                                     //buffer used to avoid race condition
  cell A;
  A.host[0]=A.guest[0]=id*2;                         //Initialize
  A.host[1]=A.guest[1]=id*2+1;
  right=(id+1)%p;
  left=id-1;
  if(left<0)
	left=p-1; 
	
  //pass0
  sumprocess+=energy(A);	


  cout<<"pass: "<<pass<<" process ID: "<<id<<" Eproc: "<<sumprocess<<" guest atoms: "<<A.guest[0]<<' '<<A.guest[1]<<'\n';
  request = MPI::COMM_WORLD.Irecv(buffer, 2, MPI::INT, left, 0);	
  MPI::COMM_WORLD.Send(A.guest, 2, MPI::INT, right, 0);
  request.Wait(); 
  A.guest[0]=buffer[0];
  A.guest[1]=buffer[1];
  
  //pass1
  sumprocess+=energy(A);
  pass++;
  cout<<"pass: "<<pass<<" process ID: "<<id<<" Eproc: "<<sumprocess<<" guest atoms: "<<A.guest[0]<<' '<<A.guest[1]<<'\n';
  
  request = MPI::COMM_WORLD.Irecv(buffer, 2, MPI::INT, left, 0);	
  MPI::COMM_WORLD.Send(A.guest, 2, MPI::INT, right, 0);
  request.Wait(); 
  A.guest[0]=buffer[0];
  A.guest[1]=buffer[1];
  
  //pass2
  if(id==0 ||id==1)
	sumprocess+=energy(A);

  pass++;
  cout<<"pass: "<<pass<<" process ID: "<<id<<" Eproc: "<<sumprocess<<" guest atoms: "<<A.guest[0]<<' '<<A.guest[1]<<'\n';
  MPI::COMM_WORLD.Reduce ( &sumprocess, &sumtotal, 1, MPI::DOUBLE, MPI::SUM, 0 );
    
  
  if(id==0)
  {

    wtime = MPI::Wtime ( )-wtime;                      //calculate the elapsed wall time
	cout << "Energy calculated by parallel programming is: "<<sumtotal<<'\n';
	cout<<"time elapsed: "<<wtime<<'\n';

	cout << "Energy calculated by sequential program is: "<<sequential(wtime)<<'\n';
	cout<<"time elapsed: "<<wtime<<'\n';
  }


  MPI::Finalize ( );                                   //finalize
  return 0;
}
//****************************************************************************

double energy ( const cell &A )
{
	double result=0;
	if(A.host[0]!=A.guest[0])
	{
		result+=e(A.host[0],A.guest[0]);
		result+=e(A.host[0],A.guest[1]);
		result+=e(A.host[1],A.guest[0]);
		result+=e(A.host[1],A.guest[1]);
	}
	else
		result+=e(A.host[0],A.guest[1]);
	return result;
}

double sequential(double &time)
{
	time=MPI::Wtime ();
	double result=0;
	for(int i=0; i<8; ++i)
		for(int j=i+1; j<8; ++j)
				result+=e(i,j);
	time = MPI::Wtime ( )-time;
	return result;
	
}

double e(double i, double j)
{
	return sqrt(i+j);
}
