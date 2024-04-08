#ifdef DBL
    typedef double real;
#else
    typedef float real;
#endif

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <omp.h>
#include <cmath>

using namespace std;

// alpha = (x,y), x[N], y[N], N=N*M.

int main(int argc, char *argv[])
{
    int M = atoi(argv[1]);
    int N = atoi(argv[2]);
    int v = atoi(argv[3]);
    cout << "M=" << M << "\tN=" << N << "\tv=" << v << endl;

    real *x,*y, gamma;
    real alpha = v*1.e-2, beta= v*1.e-1, tmp;
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
	    tmp=x[i];
    }

end = omp_get_wtime();
cout << setprecision(3) << "B=" << ((3.0*N*sizeof(real))*1e-9)/(end-begin) << " Gbyte/s\n";

for(int threads=1; threads<5; threads++)
{
begin=omp_get_wtime();
    gamma=0.0;
omp_set_num_threads(threads);
#pragma omp parallel for reduction(+:gamma) 
    for(int i=0;i<N;i++){
	gamma += (x[i]*y[i]);
    }
end = omp_get_wtime(); 
cout << "Number of threads=" << threads <<"\n";
cout << setprecision(3) << "I=" << (2.0*N)/(2.0*N*sizeof(real)) << " FLOP/byte\n";
cout << setprecision(3) << "P=" << ((2.0e-9)*N)/(end-begin) << " GFLOP/s\n";
cout << setprecision(3) << "T=" << (end-begin) << " s\n";
cout << "gamma=" << gamma << "\n";
}

    delete [] x;  delete [] y;
    return 0;
}
