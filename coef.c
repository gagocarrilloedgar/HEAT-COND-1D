#include "headers.h"

void vectori(int N,double Tin[],double Tinincial){

	for (int i = 0; i<N; ++i)
    	{
    		*(Tin+i)=Tinincial;
    	}

}
void coef0(double a[],int deltat, int N,double rho, double vp[],double cp)//ap'
{
	for (int i = 1; i < N; ++i)
	{
		a[i]=(rho*vp[i]*cp)/((double)deltat);
	}

}
void coef1(double a[],int N,double S[],double delta,double *lamda,double beta,int op){ // aw and ae

	if (op==1)
	{
		for (int i =1; i <N; ++i) // empezamos en 1 ya que depués tendremos que aplicar condiciones de contorno
		{
			*(a+i)=beta*(1.*lamda[i]*S[i])/delta;
		}
	
	}

	if (op==2)
	{
		for (int i =1; i <N; ++i) // empezamos en 1 ya que depués tendremos que aplicar condiciones de contorno
		{
			*(a+i)=(1-beta)*(1.*lamda[i]*S[i])/delta;
		}
	
	}
		
	return;
}

void coef2(double a[],int N,double T,double alpha, double A[],double aw[],double ae[],double *Tin,double *ap){ // bp

	for (int i = 1; i <N; ++i)
	{
		*(a+i)=A[i]*T*alpha + aw[i]*Tin[i-1] + ae[i]*Tin[i+1] + ap[i]*Tin[i];
	}
return;
}

void coef2_2(double a[],int N,double T,double Textr,double alpha,double alphaextr, double A[],double aw[],double *Tin,double *ap)
{ 

	*(a+N-1)=A[N]*T*alpha + aw[N]*Tin[N-2] + ap[N]*Tin[N]+alphaextr*Textr*A[N];
	return;
}

void coef3(double a1[],double a2[],double b[],double a[],int N){ //ap

	for (int i = 1; i <N; ++i)
	{
		*(a+i)=*(a1+i)+*(a2+i)+*(b+i);
	}
return;
}