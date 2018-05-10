#include "headers.h"

void temp(double T[],double Tfut[],int N,double ap[],double ae[],double aw[],double bp[] ){

		for (int i =1; i <N; ++i)
    	{
    		*(T+i)=(ae[i]*Tfut[i+1]+aw[i]*Tfut[i-1]+bp[i])/ap[i];
    	}
}

int max(double T[],double Tin[],int N, double delta ){

	double max=0.0,x;

	for (int i = 0; i < N; ++i)
	{
		x=fabs(T[i]-Tin[i]);

		if(x>max){
			max=x;
			printf("max =%f \n", max);
		}
	}

printf("max=%f \n",max);

	if (max<delta)
		return 1;

	else return 0;


}
