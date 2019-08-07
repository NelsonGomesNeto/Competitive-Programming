#include <bits/stdc++.h>
using namespace std;

void printMatrix(vector<vector<double> > matrix, int n)
{
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
      printf("%.3lf%c", matrix[i][j], j < n - 1 ? ' ' : '\n');
}

void matrixMult(vector<vector<double> >& a, vector<vector<double> > b, int n)
{
  vector<vector<double> > ans(n);
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
    {
      ans[i].push_back(0);
      for (int k = 0; k < n; k ++)
        ans[i][j] += a[i][k] * b[k][j];
    }
  for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++) a[i][j] = ans[i][j];
}

void matrixExp(vector<vector<double> >& matrix, int n, int k)
{
  vector<vector<double> > aux(n); for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++) aux[i].push_back(i == j);
  while (k)
  {
    if (k & 1) matrixMult(aux, matrix, n);
    matrixMult(matrix, matrix, n);
    k /= 2;
  }
  for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++) matrix[i][j] = aux[i][j];
}

int main()
{
  int n, k;
  while (scanf("%d %d", &n, &k) != EOF)
  {
    vector<vector<double> > matrix(n); double x;
    for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++)
    {
      scanf("%lf", &x);
      matrix[i].push_back(x);
    }
    // printMatrix(matrix, n);
    matrixExp(matrix, n, k);
    printMatrix(matrix, n);
  }
  return(0);
}
