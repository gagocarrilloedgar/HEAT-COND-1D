#include "headers.h"

void vectori(int N,double Tin[],double Tinincial){

	for (int i = 0; i<N; ++i)
    	{
    		*(Tin+i)=Tinincial;
    	}

}

void coef1(double a[],int N,double S[],double delta,double y){ // aw and ae

		for (int i =1; i <N; ++i) // empezamos en 1 ya que depués tendremos que aplicar condiciones de contorno
		{
			*(a+i)=(1.*y*S[i])/delta;
		}
	
	return;
}
void coef2(double a[],int N,double T,double alpha, double A[]){ // bp

	for (int i = 1; i <N; ++i)
	{
		*(a+i)=A[i]*T*alpha;
	}
return;

}

void coef3(double a1[],double a2[],double b[],double a[],int N){ //ap

	for (int i = 1; i <N; ++i)
	{
		*(a+i)=*(a1+i)+*(a2+i)+*(b+i);
	}
return;
}