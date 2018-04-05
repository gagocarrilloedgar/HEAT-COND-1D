#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <strings.h>

#define PI 3.14159265358979323846;

//----------------------------------------HEAT-COND-FUNCTIONS-----------------------------------------------
// Data inputs
struct properties prop_input();
struct initial_temperatures temp_input();
struct control control_input();
struct geometry geometry_input();

void linspace(double a, double b, int n, double p[],int op);
void Area(double ef, double r[],double S[],int N);
void perimetro(double r[],double r1[],double A[],int N);
void vectori(int N,double Tin[],double Tinincial);
void vol(double V[],double A[],int Ra,int N);

void coef0(double a[],double deltat, int N,double rho, double vp[],double cp);
void coef1(double a[],int N,double S[],double delta,double *lamda,double beta,int op);
void coef2(double a[],int N,double T,double alpha, double A[],double aw[],double ae[],double *Tin,double *ap,double beta);
void coef2_2(double a[],int N,double T,double alpha, double A[],double S[],double aw[],double *Tin,double *ap,double beta);
void coef3(double a1[],double a2[],double a[],int N,double beta,double a3[]);
void temp(double T[],double Tin[],int N,double ap[],double ae[],double aw[],double bp[]);
int max(double T[],double Tin[],int N, double delta );
void lambda(double *x,int N,double *T,double k,int op);

// --------------------------------------------DATA STRUCTURE DEFINITION--------------------------------------

struct initial_temperatures //init_temp
{
	double Twall,Text,Textr,T0, T1; // to initialize Tin and Tfut

};

struct properties //prop
{
	double rho,cp,alphaextr, alphaexte,lambdaf;
	// lamda of the fin
	// density

};

struct control //cont
{
	int N;
	double deltat, deltar,delta,beta;

};

struct geometry //geo
{
	double Ra,Rb,ef;
	// initial and ending radius
	// fin thickness
};

struct vectors //e,p,w
{
	double *S;
	double *r;
	double *lambda,*lambdan;
	double *a,*an;
};

struct control_point//point
{
	double *vp;
	double *Ap;
	double *bp;
};

struct temperatures//Temp
{
	double *T,*Tin,*Tfut;

};

struct send
{
	double *S,*R;
};

struct limits
{
	int start;
	int end;
	int width;
};
