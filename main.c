#include "headers.h"

int main()
{
	//1. Definición de las entradas del programa 
	int N=10,M=N+1;
	double lamdaf=250/*lambda [W/(m*k)]*/,delta=0.01,Texterior=50.0,Textremo=30.0; // variables
	double  Twall=71.87,alphaextremo=0.33,alphaexterior=30,/* alpha[1/ºC]*/deltar,T0=10;  // variables
	double *Se,*Sw,*Ap,*Tin,*T,*r,*rw,*re ;// vectores
	double *aw,*ae,*ap,*bp,Ra=1,Rb=10,op=0,ef=1;

	// creamos un espacio dinámico para los vecto=res que utilizaremos.
	// Geometria 
	r=(double *)malloc(sizeof(double)*N);
	re=(double *)malloc(sizeof(double)*(N));
	rw=(double *)malloc(sizeof(double)*(N));
	Se=(double *)malloc(sizeof(double)*(N));
	Sw=(double *)malloc(sizeof(double)*(N));
	Ap=(double *)malloc(sizeof(double)*(N));

	// Temperaturas
	T=(double *)malloc(sizeof(double)*N);
	Tin=(double *)malloc(sizeof(double)*N);

	// Coeficientes
	aw=(double *)malloc(sizeof(double)*N);
	ae=(double *)malloc(sizeof(double)*N);
	ap=(double *)malloc(sizeof(double)*N);
	bp=(double *)malloc(sizeof(double)*N);


	  if (r==NULL || re==NULL || rw==NULL) 
    {
        printf("Out of memory\n");
        exit(1);
    }

	//2.Cálculos previos (Geometria) 
	deltar=(double)(Rb-Ra)/(N-1);

    linspace(Ra,Rb,N,rw,1);
    linspace(Ra,Rb,N,r,2); 
    linspace(Ra,Rb,N,re,3); 
    *(r+N)=Rb;

    Area(ef,rw,Sw,N);
    Area(ef,re,Se,N);
    perimetro(re,rw,Ap,N);

    // 3. Mapa incial de temperaturas
    vectori(N,Tin,T0);

    //4. Coeficientes de discretización
    coef1(aw,N,Sw,delta,lamdaf);
    coef1(ae,N,Se,delta,lamdaf);
    coef2(bp,N,Texterior,alphaexterior,Ap);
    coef3(aw,ae,bp,ap,N);

    //condiciones de contorno(i=0)--> primer elemento
    *(ap+0)=1;
    *(ae+0)=0;
    *(bp+0)=Twall;
    *(aw+0)=0;

    //condiciones de contorno(i=N+1) --> último elemento 
    *(ae+N-1)=0;
    

    // 5 Aplicación de GAUSS-SEIDEL 
	temp(T,Tin, N, ap,ae,aw,bp);
    //condiciones de contorno de T
    *(T+0)=Twall;
    for (int i = 0; i < N; ++i)
    {
    	printf("T=%f i=%d \n",*(T+i),i );
    }
    
    
    int ok=max(T,Tin,N,delta);	
    printf("ok =%d \n",ok );

    while(ok==0){

    	for (int i = 0; i < N; ++i)
    	{
    		*(Tin+i)=*(T+i);
    	}

    	temp(T,Tin, N, ap,ae,aw,bp);
    	ok=max(T,Tin,N,delta);
    	printf("ok=%d \n", ok);

    	for (int i = 0; i < N; ++i)
    	{
    		printf("T=%f i=%d \n",*(T+i),i );
   		}
    
    	
    }
    printf("\n");
    for (int i = 0; i < N; ++i)
    {
    	printf("ae=%f ap=%f aw=%f bp=%f \n",*(ae+i),*(ap+i),*(aw+i),*(bp+i) );
    }

    
    free(r);free(re);free(rw);free(Se);free(Sw);free(Ap);free(Tin);

	return 0;
}
