#include "headers.h"
/*
void InitialConfigurations(struct geometry *geo,struct initial_temperatures *init_temp,struct vectors *e,struct control *cont,struct vectors *p,struct vectors *w)
{
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
}
*/
