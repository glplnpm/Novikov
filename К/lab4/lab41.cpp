#include <mpi.h>
#ifdef DBL
    typedef double real;
    MPI_Datatype mpireal = MPI_DOUBLE;
#else
    typedef float real;
    MPI_Datatype mpireal = MPI_FLOAT;
#endif

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// alpha = (x,y), x[N], y[N], N=N*M.

int main(int argc, char *argv[])
{
    int M = atoi(argv[1]);
    int N = atoi(argv[2]);
    int v = atoi(argv[3]);


    real *x,*y, gamma, gamma_sum;
    real alpha = v*1.e-2, beta= v*1.e-1;
    MPI_Comm world = MPI_COMM_WORLD;
    int np, id;
    double begin=0, end=0;

    N=N*M;
    x = new real[N];
    y = new real[N];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(world,&np);
    MPI_Comm_rank(world,&id);


    MPI_Barrier(world);
begin = MPI_Wtime();

    for(int i=0;i<N;i++){
	x[i]=alpha;
    }

    for(int i=0;i<N;i++){
	y[i]=beta;
    }

    for(int i=0;i<N;i++){
	gamma=x[i];
    }
    MPI_Barrier(world);
end = MPI_Wtime();

if(id==0){
    cout << "M=" << M << "\tN=" << N << "\tv=" << v << endl;
    cout << setprecision(3) << "B=" << ((3.0*N*sizeof(real))*1e-9)/(end-begin) << " Gbyte/s\n";
}

MPI_Barrier(world);
begin=MPI_Wtime();
    gamma=0.0;
int Ni=N/np;
    for(int i=Ni*id;i<(Ni*(id+1));i++){
	gamma += (x[i]*y[i]);
    }
    MPI_Allreduce(&gamma,&gamma_sum,1,mpireal,MPI_SUM,world);
MPI_Barrier(world);
end = MPI_Wtime(); 

if(id==0)
{
cout << "Number of processes=" << np <<"\n";
cout << setprecision(3) << "I=" << (2.0*N)/(2.0*N*sizeof(real)) << " FLOP/byte\n";
cout << setprecision(3) << "P=" << ((2.0e-9)*N)/(end-begin) << " GFLOP/s\n";
cout << setprecision(3) << "T=" << (end-begin) << " s\n";
cout << "gamma=" << gamma_sum << "\n";
}

    MPI_Finalize();

    delete [] x;  delete [] y;
    return 0;
}
