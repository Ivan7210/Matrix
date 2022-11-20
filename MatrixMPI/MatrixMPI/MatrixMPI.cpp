#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define N 20
#define P 210
#define M 210

using namespace std;

int main(int argc, char* argv[])
{
	for (int t = 0; t < 10000; t++) {
		int tid, nthreads, i, j, k;
		double a[N][P], b[P][M], c[N][M];

#pragma omp parallel shared(a,b,c,nthreads) private(tid,i,j,k)
		{
			tid = omp_get_thread_num();

#pragma omp for
			for (i = 0; i < N; i++)
				for (j = 0; j < P; j++)
					a[i][j] = i + j;
#pragma omp for
			for (i = 0; i < P; i++)
				for (j = 0; j < M; j++)
					b[i][j] = i * j;
#pragma omp for
			for (i = 0; i < N; i++)
				for (j = 0; j < M; j++)
					c[i][j] = 0;


			//cout << "Thread " << tid << " starting matrix multiply…\n";

#pragma omp for
			for (i = 0; i < N; i++)
			{
				//cout << "Thread=" << tid << "dead row =" << i << "\n";
				for (j = 0; j < M; j++)
					for (k = 0; k < P; k++)
						c[i][j] += a[i][k] * b[k][j];
			}

		}
	}
	return(0);
}