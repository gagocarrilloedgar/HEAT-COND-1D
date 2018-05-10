#include "headers.h"

void ControlFichero(char *path,int K,double *V,int N,int argc , char **arg)
{
  // hay que añadir que imprima en el ficherp también el vector posición
  int e = EXIT_SUCCESS;
Beautify
  const char* nombre;
  FILE *file = fopen(nombre, "w");

  if (K==0)
  {
    nombre="Temperatures.txt";
    FILE *file = fopen(nombre, "w");
  }
  else
  {
    nombre="Coeficientes.txt";
    FILE *file = fopen(nombre, "w");
  }

  if(!file)
  {
    perror(nombre);
    return EXIT_FAILURE;
  }

  if (file)
  {
    fprintf(file," Distribution %s: \n", nombre);
    for (int i; i<N; i++)
    {
      fprintf(file, "%f \n", V[i] );
    }

    return EXIT_SUCCESS;
  }

  if (fputs("Output in file.\n", file) == EOF)
  {
    perror(nombre);
    e = EXIT_FAILURE;
  }

  if (fclose(file))
  {
    perror(nombre);
    return EXIT_FAILURE;
  }

}
