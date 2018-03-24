#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979323846;

void linspace(double a, double b, int n, double p[],int op);
void Area(int ef, double r[],double S[],int N);
void perimetro(double r[],double r1[],double A[],int N);
void vectori(int N,double Tin[],double Tinincial);
void coef1(double a[],int N,double S[],double delta,double y);
void coef2(double a[],int N,double T,double alpha, double A[]);
void coef3(double a1[],double a2[],double b[],double a[],int N);
void temp(double T[],double Tin[],int N,double ap[],double ae[],double aw[],double bp[]);
int max(double T[],double Tin[],int N, double delta );