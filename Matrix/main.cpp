
#include "matrix.h"
#include <time.h>

const int Smax = 3000 ;

void main()
{
	double time;
	clock_t start,finish;
	TMatrix<int> a(Smax), b(Smax), c(Smax);

	for (int i = 0; i < Smax; i++)
    for (int j = 0; j < Smax; j++ )
		{
			a[i][j] =  i * 10 + j;
			b[i][j] = (i * 10 + j) * 100;
		 }

	//cout << "Matrix a = " << endl << a << endl;
	//cout << "Matrix b = " << endl << b << endl;
	start=clock();
	c=a+b;
	finish=clock();
	/*cout << "Matrix c = a + b" << endl << c << endl;*/
	 
	 time=(double)(finish-start)/(double)CLOCKS_PER_SEC;
	 cout << "time" << time << endl;
}