#include "headers.h"

void linspace(double Ra, double Rb, int N, double r[],int op)
{
	double c=0.0,k=0.0;
	c=(Rb - Ra)/((double)N-1);


	for (int i = 0; i <N; ++i)
	{
		k= Ra+(double)i*(c);

		if (op==1)
			*(r+i)=k-c/2;
		if (op==3)
			*(r+i)=k+c/2;
	}

	for (int i = 0; i <=N; ++i)
	{
		k= Ra+(double)i*(c);

		if (op==2)
			*(r+i)=k;
	}

	return;
}
