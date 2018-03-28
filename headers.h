#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979323846;

void linspace(double a, double b, int n, double p[],int op);
void Area(double ef, double r[],double S[],int N);
void perimetro(double r[],double r1[],double A[],int N);
void vectori(int N,double Tin[],double Tinincial);
void coef0(double a[],int deltat, int N,double rho, double vp[],double cp);
void coef1(double a[],int N,double S[],double delta,double *lamda,double beta,int op);
void coef2(double a[],int N,double T,double alpha, double A[],double aw[],double ae[],double *Tin,double *ap);
void coef2_2(double a[],int N,double T,double Textr,double alpha,double alphaextr, double A[],double aw[],double *Tin,double *ap);
void coef3(double a1[],double a2[],double b[],double a[],int N);
void temp(double T[],double Tin[],int N,double ap[],double ae[],double aw[],double bp[]);
int max(double T[],double Tin[],int N, double delta );
void lambda(double *x,int N,double *T,double k,int op);
void vol(double V[],double A[],int Ra,int N);