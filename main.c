		#include "headers.h"

int main()
{
    struct initial_temperatures init_temp;
    struct properties prop;
    struct control cont;
    struct geometry geo;
    struct vectors *e,*p,*w;
    struct control_point *point;
    struct temperatures *Temp;

	//1. input data definiton
    /*prop=prop_input();
    init_temp=temp_input();
    cont=control_input();
    geo=geometry_input();
    */
    init_temp.Twall=40;
    init_temp.Text=25;
    init_temp.Textr=30;
    init_temp.T0=10;
    init_temp.T1=4;

    prop.rho=2300;
    prop.cp=1;
    prop.alphaexte=300;
    prop.alphaextr=350;
    prop.lambdaf=70;

    cont.N=20;
    cont.deltat=1;
    cont.delta=0.01;
    cont.beta=1;

    geo.Ra=0.03;
    geo.Rb=0.1;
    geo.ef=0.01;

	// --------------------Dynamic space for matrix and vector------------------------------------------------------
	// Vectors 
    e=(struct vectors*)malloc(sizeof(struct vectors));
        e->S=(double *)malloc(sizeof(double)*cont.N);
        e->r=(double *)malloc(sizeof(double)*cont.N);
        e->lambda=(double *)malloc(sizeof(double)*cont.N);
        e->lambdan=(double *)malloc(sizeof(double)*cont.N);
        e->a=(double *)malloc(sizeof(double)*cont.N);
        e->an=(double *)malloc(sizeof(double)*cont.N);

        if (e->S==NULL || e->r==NULL || e->lambda==NULL || e->lambdan==NULL || e->a==NULL || e->an==NULL) 
        {
            printf("Out of memory\n");
            exit(1);
        }

     w=(struct vectors*)malloc(sizeof(struct vectors));
        w->S=(double *)malloc(sizeof(double)*cont.N);
        w->r=(double *)malloc(sizeof(double)*cont.N);
        w->lambda=(double *)malloc(sizeof(double)*cont.N);
        w->lambdan=(double *)malloc(sizeof(double)*cont.N);
        w->a=(double *)malloc(sizeof(double)*cont.N);
        w->an=(double *)malloc(sizeof(double)*cont.N);

        if (w->S==NULL || w->r==NULL || w->lambda==NULL || w->lambdan==NULL || w->a==NULL || w->an==NULL) 
        {
            printf("Out of memory\n");
            exit(1);
        }

     p=(struct vectors*)malloc(sizeof(struct vectors));
        p->S=(double *)malloc(sizeof(double)*cont.N);
        p->r=(double *)malloc(sizeof(double)*cont.N);
        p->lambda=(double *)malloc(sizeof(double)*cont.N);
        p->lambdan=(double *)malloc(sizeof(double)*cont.N);
        p->a=(double *)malloc(sizeof(double)*cont.N);
        p->an=(double *)malloc(sizeof(double)*cont.N);

        if (p->S==NULL || p->r==NULL || p->lambda==NULL || p->lambdan==NULL || p->a==NULL || p->an==NULL) 
        {
            printf("Out of memory\n");
            exit(1);
        }

    // Control points 
    point=(struct control_point*)malloc(sizeof(struct control_point));
        point->vp=(double *)malloc(sizeof(double)*cont.N);
        point->Ap=(double *)malloc(sizeof(double)*cont.N);
        point->bp=(double *)malloc(sizeof(double)*cont.N);

        if (point->vp==NULL || point->Ap==NULL || point->bp==NULL) 
        {
            printf("Out of memory\n");
            exit(1);
        }

    // Temperatures
    Temp=(struct temperatures *)malloc(sizeof(struct temperatures));
        Temp->T=(double *)malloc(sizeof(double)*cont.N);
        Temp->Tin=(double *)malloc(sizeof(double)*cont.N);
        Temp->Tfut=(double *)malloc(sizeof(double)*cont.N);

         if (Temp->T==NULL || Temp->Tin==NULL || Temp->Tfut==NULL) 
        {
            printf("Out of memory\n");
            exit(1);
        }

	//2.Cálculos previos (Geometria) 

    //2.Cálculos previos (Geometria) 
	cont.deltar=(geo.Rb-geo.Ra)/(double)(cont.N-1);

    linspace(geo.Ra,geo.Rb,cont.N,w->r,1); //rw
    linspace(geo.Ra,geo.Rb,cont.N,p->r,2); //r
    linspace(geo.Ra,geo.Rb,cont.N,e->r,3); //re
    *(p->r+cont.N)=geo.Rb;

    Area(geo.ef,w->r,w->S,cont.N);//Sw
    Area(geo.ef,e->r,e->S,cont.N);//Se
    Area(geo.ef,p->r,p->S,cont.N);//S
    perimetro(e->r,w->r,point->Ap,cont.N);//Ap
    vol(point->vp,p->S,geo.Rb-geo.Ra,cont.N);//Vp

    // 3. Mapa incial de temperaturas
    vectori(cont.N,Temp->Tin,init_temp.T0);
    vectori(cont.N,Temp->Tfut,init_temp.T1);

    //4. Coeficientes de discretización
    lambda(e->lambda,cont.N,Temp->Tin,prop.lambdaf,2);
    lambda(w->lambda,cont.N,Temp->Tin,prop.lambdaf,1);
    lambda(e->lambdan,cont.N,Temp->Tfut,prop.lambdaf,2);
    lambda(w->lambdan,cont.N,Temp->Tfut,prop.lambdaf,1);

    coef0(p->an,cont.deltat,cont.N,prop.rho,point->vp,prop.cp);
    coef1(w->a,cont.N,w->S,cont.deltar,w->lambda,cont.beta,1);//aw
    coef1(e->a,cont.N,e->S,cont.deltar,e->lambda,cont.beta,1);//ae
    coef1(e->an,cont.N,e->S,cont.deltar,e->lambda,cont.beta,2);//aen
    coef1(w->an,cont.N,w->S,cont.deltar,w->lambda,cont.beta,2);//awn
    coef2(point->bp,cont.N,init_temp.Text,prop.alphaexte,point->Ap,w->an,e->an,Temp->Tin,p->an);//bp
    coef2_2(point->bp,cont.N,init_temp.Text,init_temp.Textr,prop.alphaexte,prop.alphaextr,point->Ap,w->an,Temp->Tin,p->an);
    coef3(w->a,e->a,p->an,p->a,cont.N); //ap

    //condiciones de contorno(i=0)--> primer elemento
    *(p->a+0)=1;
    *(e->a+0)=0;
    *(point->bp+0)=init_temp.Twall;
    *(w->a+0)=0;

    //condiciones de contorno(i=N+1) --> último elemento 
    *(e->a+cont.N-1)=0;
    
    // 5 Aplicación de GAUSS-SEIDEL 
	temp(Temp->T,Temp->Tfut, cont.N, p->a,e->a,w->a,point->bp);
    //condiciones de contorno de T
    *(Temp->T+0)=init_temp.Twall;

    for (int i = 0 ; i < cont.N; ++i)
    {
    	printf("T=%f i=%d \n",*(Temp->T+i),i );
    }
    
    int ok=max(Temp->T,Temp->Tin,cont.N,cont.delta);	
    printf("ok =%d \n",ok );

    while(ok==0){
    	linspace(geo.Ra,geo.Rb,cont.N,w->r,1); //rw
    	linspace(geo.Ra,geo.Rb,cont.N,p->r,2); //r
    	linspace(geo.Ra,geo.Rb,cont.N,e->r,3); //re
    	*(p->r+cont.N)=geo.Rb;

    	Area(geo.ef,w->r,w->S,cont.N);//Sw
    	Area(geo.ef,e->r,e->S,cont.N);//Se
    	Area(geo.ef,p->r,p->S,cont.N);//S
    	perimetro(e->r,w->r,point->Ap,cont.N);//Ap
    	vol(point->vp,p->S,geo.Rb-geo.Ra,cont.N);//Vp

	    // 3. Mapa incial de temperaturas
    	vectori(cont.N,Temp->Tin,init_temp.T0);
    	vectori(cont.N,Temp->Tfut,init_temp.T1);

    	//4. Coeficientes de discretización
    	lambda(e->lambda,cont.N,Temp->Tin,prop.lambdaf,2);
    	lambda(w->lambda,cont.N,Temp->Tin,prop.lambdaf,1);
    	lambda(e->lambdan,cont.N,Temp->Tfut,prop.lambdaf,2);
    	lambda(w->lambdan,cont.N,Temp->Tfut,prop.lambdaf,1);

	    coef0(p->an,cont.deltat,cont.N,prop.rho,point->vp,prop.cp);
	    coef1(w->a,cont.N,w->S,cont.deltar,w->lambda,cont.beta,1);//aw
   	 	coef1(e->a,cont.N,e->S,cont.deltar,e->lambda,cont.beta,1);//ae
    	coef1(e->an,cont.N,e->S,cont.deltar,e->lambda,cont.beta,2);//aen
    	coef1(w->an,cont.N,w->S,cont.deltar,w->lambda,cont.beta,2);//awn
	    coef2(point->bp,cont.N,init_temp.Text,prop.alphaexte,point->Ap,w->an,e->an,Temp->Tin,p->an);//bp
	    coef2_2(point->bp,cont.N,init_temp.Text,init_temp.Textr,prop.alphaexte,prop.alphaextr,point->Ap,w->an,Temp->Tin,p->an);
	    coef3(w->a,e->a,p->an,p->a,cont.N); //ap

    	//condiciones de contorno(i=0)--> primer elemento
    	*(p->a+0)=1;
    	*(e->a+0)=0;
    	*(point->bp+0)=init_temp.Twall;
    	*(w->a+0)=0;

    	//condiciones de contorno(i=N+1) --> último elemento 
   	 	*(e->a+cont.N-1)=0;
        

    	for (int i = 0; i < cont.N; ++i)
    	{
    		*(Temp->Tin+i)=*(Temp->T +i);
            *(Temp->Tfut+i)=*(Temp->T +i);
    	}

        // recalculating temperatures
    	temp(Temp->T,Temp->Tin,cont.N,p->a,e->a,w->a,point->bp);
    	ok=max(Temp->T,Temp->Tin,cont.N,cont.delta);
    	printf("ok=%d \n", ok);

    	for (int i = 0; i < cont.N; ++i)
    	{
    		printf("T=%f i=%d \n",*(Temp->T+i),i );
   		}
    	
    }
    printf("\n");
    for (int i = 0; i <cont.N; ++i)
    {
    	printf("ae=%f ap=%f aw=%f bp=%f \n",*(e->a+i),*(p->a+i),*(w->a+i),*(point->bp+i) );
    }
	
   free(e->r); free(e->S); free(e->lambda); free(e->lambdan); free(e->a); free(e->an); free(e); 
   free(w->r); free(w->S); free(w->lambda); free(w->lambdan); free(w->a); free(w->an); free(w); 
   free(p->r); free(p->S); free(p->lambda); free(p->lambdan); free(p->a); free(p->an); free(p); 

   free(point->vp); free(point->Ap); free(point->bp);

   free(Temp->T); free(Temp->Tin); free(Temp->Tfut);

	return 0;
}

