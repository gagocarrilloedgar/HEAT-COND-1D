#include "headers.h"

int main()
{
	//1. Definición de las entradas del programa 
	int N=10,M=N+1,Ra=1,Rb=10,op=0,ef=1;
	double lamdaf=250/*lambda [W/(m*k)]*/,delta=0.1,Texterior=50.0,Textremo=40,rho=10; // variables
	double  Twall=71.87,alphaextremo=5,alphaexterior=30,/* alpha[1/ºC]*/deltar,T0=10;  // variables
    double cp=0.7,deltat=3,T1=4,beta=0.5; // T1--> T(n+1)*
	double *Se,*Sw,*S,*Ap,*Tin,*T,*r,*rw,*re,*lamdae,*lamdaw,*Tfut;// vectores
	double *aw,*ae,*ap,*bp,*apn,*vp,*awn,*aen,*lamdaen,*lamdawn; // k1 y k2 para hacer más fácil coef2

	// creamos un espacio dinámico para los vecto=res que utilizaremos.
	// Geometria 
	r=(double *)malloc(sizeof(double)*N);
	re=(double *)malloc(sizeof(double)*(N));
	rw=(double *)malloc(sizeof(double)*(N));
    S=(double *)malloc(sizeof(double)*(N));
	Se=(double *)malloc(sizeof(double)*(N));
	Sw=(double *)malloc(sizeof(double)*(N));
	Ap=(double *)malloc(sizeof(double)*(N));

	// Temperaturas
	T=(double *)malloc(sizeof(double)*N);
	Tin=(double *)malloc(sizeof(double)*N);
    Tfut=(double *)malloc(sizeof(double)*N);

	// Coeficientes
	aw=(double *)malloc(sizeof(double)*N);
	ae=(double *)malloc(sizeof(double)*N);
	ap=(double *)malloc(sizeof(double)*N);
	bp=(double *)malloc(sizeof(double)*N);

    aen=(double *)malloc(sizeof(double)*N);
    awn=(double *)malloc(sizeof(double)*N);
    apn=(double *)malloc(sizeof(double)*N);
    vp=(double *)malloc(sizeof(double)*N);


	  if (r==NULL || re==NULL || rw==NULL || S==NULL) 
    {
        printf("Out of memory\n");
        exit(1);
    }

      if (ae==NULL || aw==NULL || ap==NULL || bp==NULL) 
    {
        printf("Out of memory\n");
        exit(1);
    }
     if (aen==NULL || awn==NULL || apn==NULL || vp==NULL) 
    {
        printf("Out of memory\n");
        exit(1);
    }

	//2.Cálculos previos (Geometria) 
	deltar=(double)(Rb-Ra)/(N-1);

    linspace(Ra,Rb,N,rw,1); //rw
    linspace(Ra,Rb,N,r,2); //r
    linspace(Ra,Rb,N,re,3); //re
    *(r+N)=Rb;

    Area(ef,rw,Sw,N);//Sw
    Area(ef,re,Se,N);//Se
    Area(ef,r,S,N);//S
    perimetro(re,rw,Ap,N);//Ap
    vol(vp,S,Rb-Ra,N);//Vp

    // 3. Mapa incial de temperaturas
    if (T==NULL || Tin==NULL || Tfut==NULL) 
    {
        printf("Out of memory\n");
        exit(1);
    }
    vectori(N,Tin,T0);
    vectori(N,Tfut,T1);

    //4. Coeficientes de discretización
    lamdae=(double *)malloc(sizeof(double)*N);
    lamdaen=(double *)malloc(sizeof(double)*N);
    lamdaw=(double *)malloc(sizeof(double)*N);
    lamdawn=(double *)malloc(sizeof(double)*N);

     if (lamdaw==NULL || lamdae==NULL || lamdawn==NULL || lamdaen==NULL ) 
    {
        printf("Out of memory\n");
        exit(1);
    }

    lambda(lamdae,N,Tin,lamdaf,2);
    lambda(lamdaw,N,Tin,lamdaf,1);
    lambda(lamdaen,N,Tfut,lamdaf,2);
    lambda(lamdawn,N,Tfut,lamdaf,1);

    coef0(apn,deltat,N,rho,vp,cp);
    coef1(aw,N,Sw,deltar,lamdaw,beta,1);//aw
    coef1(ae,N,Se,deltar,lamdae,beta,1);//ae
    coef1(aen,N,Se,deltar,lamdae,beta,2);//aen
    coef1(awn,N,Se,deltar,lamdae,beta,2);//awn
    coef2(bp,N,Texterior,alphaexterior,Ap,awn,aen,Tin,apn);//bp
    coef2_2(bp,N,Texterior,Textremo,alphaexterior,alphaextremo,Ap,awn,Tin,apn);
    coef3(aw,ae,apn,ap,N); //ap

    //condiciones de contorno(i=0)--> primer elemento
    *(ap+0)=1;
    *(ae+0)=0;
    *(bp+0)=Twall;
    *(aw+0)=0;

    //condiciones de contorno(i=N+1) --> último elemento 
    *(ae+N-1)=0;
    
    // 5 Aplicación de GAUSS-SEIDEL 
	temp(T,Tfut, N, ap,ae,aw,bp);
    //condiciones de contorno de T
    *(T+0)=Twall;

    for (int i = 0 ; i < N; ++i)
    {
    	printf("T=%f i=%d \n",*(T+i),i );
    }
    
    int ok=max(T,Tin,N,delta);	
    printf("ok =%d \n",ok );

    while(ok==0){

        lambda(lamdae,N,Tin,lamdaf,2);
        lambda(lamdaw,N,Tin,lamdaf,1);
        lambda(lamdaen,N,Tfut,lamdaf,2);
        lambda(lamdawn,N,Tfut,lamdaf,1);

        coef0(apn,deltat,N,rho,vp,cp);
        coef1(aw,N,Sw,deltar,lamdaw,beta,1);//aw
        coef1(ae,N,Se,deltar,lamdae,beta,1);//ae
        coef1(aen,N,Se,deltar,lamdae,beta,2);//aen
        coef1(awn,N,Se,deltar,lamdae,beta,2);//awn
        coef2(bp,N,Texterior,alphaexterior,Ap,awn,aen,Tin,apn);//bp
        coef2_2(bp,N,Texterior,Textremo,alphaexterior,alphaextremo,Ap,awn,Tin,apn);
        coef3(aw,ae,bp,ap,N); //ap

        //condiciones de contorno(i=0)--> primer elemento
        *(ap+0)=1;
        *(ae+0)=0;
        *(bp+0)=Twall;
        *(aw+0)=0;

        //condiciones de contorno(i=N+1) --> último elemento 
        *(ae+N-1)=0;

    	for (int i = 0; i < N; ++i)
    	{
    		*(Tin+i)=*(T+i);
            *(Tfut+i)=*(T+i);
    	}

        // recalculating temperatures
    	temp(T,Tin,N,ap,ae,aw,bp);
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
    free(lamdae); free(lamdaw); free(lamdawn); free(lamdaen); free(S);
    free(vp); free(apn); free(T); free(Tfut);
    free(ae); free(aw);free(ap); free(bp); free(awn); free(aen);

	return 0;
}

