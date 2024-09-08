#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void printMatrix(int y, int x, double matrix[][x])
{
  int i, j;
  for (i = 0; i < y; i ++)
  {
    printf("(");
    for (j = 0; j < x - 1; j ++)
      printf("%.2lf, ", matrix[i][j]);
    printf("%.2lf)\n", matrix[i][j]);
  } printf("\n");
}

void printVector(int size, double vector[])
{
  int i;
  printf("(");
  for (i = 0; i < size - 1; i ++)
    printf("%.2lf, ", vector[i]);

  printf("%.2lf)", vector[i]);
}

double* multiplyVector(int size, double vector[], double multiple)
{
  double *new = malloc(size * sizeof(double));
  int i;
  for (i = 0; i < size; i ++)
  {
    new[i] = vector[i] * multiple;
  }

  return(new);
}

void sumVectors(int size, double vectorA[], double vectorB[], char type)
{
  int i;
  for (i = 0; i < size; i ++)
  {
    if (type == '+')
      vectorA[i] += vectorB[i];
    else
      vectorA[i] -= vectorB[i];
  }
}

double euclidianInnerProduct(int size, double vectorA[], double vectorB[])
{
  double result = 0; int i;
  for (i = 0; i < size; i ++)
    result += vectorA[i] * vectorB[i];

  return(result);
}

double norm(int size, double vector[])
{
  return(sqrt(euclidianInnerProduct(size, vector, vector)));
}

double** orthonormalize(int vectors, int size, double mat[][size])
{
  int i, j; //Just setting up things
  double **new = malloc(vectors * sizeof(double*));
  for (i = 0; i < vectors; i ++)
    *new = malloc(size * sizeof(double));

  double *vTemp = malloc(size * sizeof(double));
  for (i = 0; i < vectors; i ++)
  {
    vTemp = mat[i]; // vi = vTemp
    for (j = 0; j < i; j ++)
      sumVectors(size, vTemp, multiplyVector(size, new[j], euclidianInnerProduct(size, mat[i], new[j])), '-');
      // vi -= <ui, gj>gj + ... + <ui, g(i-1)>g(i-1); where new[j] = gj and mat[i] = ui

    printf("v%d = ", i + 1); printVector(size, vTemp); printf(", ||v%d|| = sqrt(%.2lf)\n", i + 1, euclidianInnerProduct(size, vTemp, vTemp));

    new[i] = multiplyVector(size, vTemp, (double) 1/norm(size, vTemp));
    // gi = vi/||vi||; where vi = vTemp and 1/||vi|| = 1/norm(size, vTemp)
  }

  return(new);
}

double* projection(int vectors, int size, double *vector, double mat[][size])
{
  int i; double *vTemp = malloc(size * sizeof(double));
  vTemp = multiplyVector(size, mat[0], euclidianInnerProduct(size, vector, mat[0]));
  for (i = 1; i < size; i ++)
    sumVectors(size, vTemp, multiplyVector(size, mat[i], euclidianInnerProduct(size, vector, mat[i])), '+');

  return(vTemp);
}

int main()
{
  int numberOfVectors; scanf("%d", &numberOfVectors);
  int vectorSize; scanf("%d", &vectorSize);
  double matrix[numberOfVectors][vectorSize]; int i, j;

  for (i = 0; i < numberOfVectors; i ++)
    for (j = 0; j < vectorSize; j ++)
      scanf("%lf", &matrix[i][j]);

  printMatrix(numberOfVectors, vectorSize, matrix);

  double **orthonormalized = malloc(numberOfVectors * sizeof(double*));
  for (i = 0; i < numberOfVectors; i ++)
    *orthonormalized = malloc(vectorSize * sizeof(double));

  orthonormalized = orthonormalize(numberOfVectors, vectorSize, matrix); printf("\n");

  for (i = 0; i < numberOfVectors; i ++)
  {
    printf("(");
    for (j = 0; j < vectorSize - 1; j ++)
      printf("%.2lf, ", orthonormalized[i][j]);
    printf("%.2lf)\n", orthonormalized[i][j]);
  } printf("\n");

  double *projected = malloc(vectorSize * sizeof(double*));
  for (i = 0; i < vectorSize; i ++)
    scanf("%lf", &projected[i]);

  for (i = 0; i < numberOfVectors; i ++)
    for (j = 0; j < vectorSize; j ++)
      matrix[i][j] = orthonormalized[i][j];

  projected = projection(numberOfVectors, vectorSize, projected, matrix);

  printVector(vectorSize, projected); printf("\n");

  return(0);
}
