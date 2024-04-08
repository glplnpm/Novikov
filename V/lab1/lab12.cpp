#ifdef DBL
typedef double real;
#else
typedef float real;
#endif

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <omp.h>

using namespace std; 

// C = A*B, A_{MxN}, B_{NxM}, C_{MxM}

int main(int argc, char *argv[])
{
    int M = atoi(argv[1]);
    int N = atoi(argv[2]);
    int v = atoi(argv[3]);
    cout << "M=" << M << "\tN=" << N << "\tv=" << v << endl;
    real *A,*B,*C;
    real alpha = v*1.e-2, beta= v*1.e-1, tmp; 
    double begin=0, end=0;

    A = new real [M*N];
    B = new real [N*M];
    C = new real [M*M];

begin = omp_get_wtime();

    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
	    A[i*N+j]= alpha;
	}
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
	    B[i*M+j]= beta;
	}
    }

    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
	    tmp=A[i*N+j];
	}
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
	    tmp=B[i*M+j];
	}
    }

end = omp_get_wtime();
cout << setprecision(3) << "B=" << ((4.0*M*N*sizeof(real))*1e-9)/(end-begin) << " Gbyte/s\n";

begin = omp_get_wtime();

 for(int i=0;i<M;i++){
   for(int j=0;j<M;j++){
     C[i*M+j]=0;
  }
 }
// ijk
 for(int i=0;i<M;i++){
   for(int j=0;j<M;j++){
     for(int k=0;k<N;k++){
        C[i*M+j]+=A[i*N+k]*B[k*M+j];
     }
   }
 }

end = omp_get_wtime();
cout << "ijk\n";
cout << setprecision(3) << "P=" << ((2.0*M*N*M)*1e-9)/(end-begin) << " GFLOP/s\n";
cout << setprecision(3) << "I=" << (1.0*M*N)/((M+N)*sizeof(real)) << " GFLOP/s\n";

    delete [] A;  delete [] B;  delete [] C;
    return 0;
}
