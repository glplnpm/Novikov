#include <iostream>
#include <iomanip>
#include <mpi.h>
#include <cmath>
#include <cstdlib>
 
using namespace std;
 
const int Nit=1;
 
typedef float real;
 
int main(int argc, char *argv[])
{
    double begin,end;
    int id, np, mi;
    MPI_Comm world=MPI_COMM_WORLD;
    MPI_Status status;
    real *A=nullptr,*B=nullptr,*C=nullptr,*Ai=nullptr,*Bi=nullptr,*Ci=nullptr;
    int M=0, N=0, v=0;


MPI_Init(&argc,&argv);
MPI_Comm_rank(world,&id);
MPI_Comm_size(world,&np);

if(!id)
{
  M=atoi(argv[1]); N=atoi(argv[2]); v=atoi(argv[3]);

    A= new real[M*N];
    B= new real[N*M];
    C= new real[M*M];

    real alpha=1.01*v, beta=0.002*v;

    for(int i=0;i<M;i++)
        for(int j=0;j<N;j++) A[i*N+j]=alpha;

    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++) B[i*M+j]=beta;
}

MPI_Barrier(world);
begin=MPI_Wtime();
if(!id)
{
    for(int i=1;i<np;i++){
	    MPI_Send(&M,1,MPI_INT,i,0,world);
	    MPI_Send(&N,1,MPI_INT,i,0,world);

	    MPI_Send(A+(M/np)*N*i,(M/np)*N,MPI_FLOAT,i,0,world);
	    MPI_Send(B,N*M,MPI_FLOAT,i,0,world);
    }

    Ci=C; Ai=A; Bi=B;
}
else
{
	MPI_Recv(&M,1,MPI_INT,0,0,world,&status);
	MPI_Recv(&N,1,MPI_INT,0,0,world,&status);

        Ai = new real[(M/np)*N];
	MPI_Recv(Ai,(M/np)*N,MPI_FLOAT,0,0,world,&status);

	Bi = new real[N*M];
	MPI_Recv(Bi,N*M,MPI_FLOAT,0,0,world,&status);

	Ci = new real[(M/np)*M];
}

 mi=(M/np);

real tmp;

    for(int i=0;i<mi;i++)
        for(int j=0;j<M;j++){
	    tmp=0;
	    for(int k=0;k<N;k++) tmp+=Ai[i*N+k]*Bi[k*M+j];
	    Ci[i*M+j]=tmp;
	}

if(!id){
    for(int i=1;i<np;i++){
	MPI_Recv(C+mi*M*i,mi*M,MPI_FLOAT,i,0,world,&status);
    }
}
else{
	MPI_Send(Ci,mi*M,MPI_FLOAT,0,0,world);
}
end=MPI_Wtime();

if(!id){
    cout << setprecision(3) << "M: "<< M << "\tN: " << N  << endl;
    cout << setprecision(3) << "p: "<< np << "\tT"<< np  << ": " << (end-begin) <<"s" << endl;

    delete [] A; delete [] B; delete [] C;
  }      
else{
	delete [] Ai; delete [] Bi; delete [] Ci;
}

MPI_Finalize();
return 0;
}
