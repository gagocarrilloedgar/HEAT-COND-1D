#include "headers.h"

void Area(int ef, double r[],double S[],int N){

	for (int i = 0; i <N; ++i)
	{
		*(S+i)= r[i]*(double)ef*2*PI;
		
	}

	return;
}

void perimetro(double r1[],double r[],double A[],int N){

	double re,rw;
	
	for (int i = 0; i < N; ++i)
	{
		re=*(r1+i);
		rw=*(r+i);

		*(A+i)=(re*re-rw*rw)*2*PI;	
	}
}

void vol(double V[],double A[],int Ra,int N)
{
	for (int i = 0; i < N; ++i)
	{
		V[i]=A[i]*(double)Ra;
	}
}
