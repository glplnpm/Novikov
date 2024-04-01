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

// gamma = (x,y), x_{N1}, y_{N1}, N1=N*M.

int main(int argc, char *argv[])
{
    int M = atoi(argv[1]);
    int N = atoi(argv[2]);
    int v = atoi(argv[3]);
    cout << "M=" << M << "\tN=" << N << "\tv=" << v << endl;
    real *x,*y;
    real alpha = v*1.e-2, beta= v*1.e-1, gamma;
    double begin=0, end=0;

    N=N*M;
    x = new real[N];
    y = new real[N];

begin = omp_get_wtime();
    for(int i=0;i<N;i++){
	x[i]=alpha;
    }

    for(int i=0;i<N;i++){
	y[i]=beta;
    }

    for(int i=0;i<N;i++){
	gamma=y[i];
    }
end = omp_get_wtime();

cout << setprecision(3) << "B=" << ((3.0*N*sizeof(real))*1e-9)/(end-begin) << " Gbyte/s\n";

//    printf("%.12f %.18f\n",(float)0.2,(double)0.2);

begin = omp_get_wtime();
gamma=0;
#pragma GCC unroll 1
    for(int i=0;i<N;i++){
	gamma+=x[i]*y[i];
    }
end = omp_get_wtime();
cout << "unroll 1\n";
cout << setprecision(3) << "I=" << 2.0*N/(3*sizeof(real)*N) << " FLOP/byte\n";
cout << setprecision(3) << "P=" << (2.0*N*1e-9)/(end-begin) << " GFLOP/s\n";
cout << setprecision(3) << "T=" << (end-begin) << " s\n";
cout << "gamma=" << gamma << "\n";

begin = omp_get_wtime();
gamma=0;
#pragma GCC unroll 2
    for(int i=0;i<N;i+=2){
	gamma+=x[i]*y[i];
    }
end = omp_get_wtime();
cout << "unroll 2\n";
cout << setprecision(3) << "I=" << 2.0*N/(3*sizeof(real)*N) << " FLOP/byte\n";
cout << setprecision(3) << "P=" << (2.0*N*1e-9)/(end-begin) << " GFLOP/s\n";
cout << setprecision(3) << "T=" << (end-begin) << " s\n";
cout << "gamma=" << gamma << "\n";

begin = omp_get_wtime();
gamma=0;
#pragma GCC unroll 3
    for(int i=0;i<N;i++){
	gamma+=x[i]*y[i];
    }
end = omp_get_wtime();
cout << "unroll 3\n";
cout << setprecision(3) << "I=" << 2.0*N/(3*sizeof(real)*N) << " FLOP/byte\n";
cout << setprecision(3) << "P=" << (2.0*N*1e-9)/(end-begin) << " GFLOP/s\n";
cout << setprecision(3) << "T=" << (end-begin) << " s\n";
cout << "gamma=" << gamma << "\n";

begin = omp_get_wtime();
gamma=0;
#pragma GCC unroll 4
    for(int i=0;i<N;i++){
	gamma+=x[i]*y[i];
    }
end = omp_get_wtime();
cout << "unroll 4\n";
cout << setprecision(3) << "I=" << 2.0*N/(3*sizeof(real)*N) << " FLOP/byte\n";
cout << setprecision(3) << "P=" << (2.0*N*1e-9)/(end-begin) << " GFLOP/s\n";
cout << setprecision(3) << "T=" << (end-begin) << " s\n";
cout << "gamma=" << gamma << "\n";

    delete [] x; delete [] y;
    return 0;
}
