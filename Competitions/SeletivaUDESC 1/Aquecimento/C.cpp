#include <bits/stdc++.h>
using namespace std;
int n;

double grade(pair<double, double> aluno[], int pa)
{
  double g = 0, w = 1;
  for (int i = 0; i < n - 1; i ++)
  {
    g += aluno[i].first * aluno[i].second;
    w -= aluno[i].second;
  }
  return(g + pa*w);
}

int main()
{
  while (scanf("%d", &n) && n)
  {
    pair<double, double> aluno[n - 1]; double a, b;
    for (int i = 0; i < n - 1; i ++)
    {
      scanf("%lf %lf", &a, &b);
      aluno[i].first = a; aluno[i].second = b;
    }
    double pa; scanf("%lf", &pa);

    printf("%s\n", grade(aluno, pa) >= 5 ? "aprovado" : "volte no exame");
  }

  return(0);
}