#include <bits/stdc++.h>
using namespace std;
int array[(int) 2e5], n;

double evaluate(double guess)
{
  double slo = 0, shi = 0, blo = -1e6, bhi = -1e6;
  for (int i = 0; i < n; i ++)
  {
    slo += (array[i] - guess) * (-1);
    shi += (array[i] - guess);
    if (slo > blo) blo = slo;
    if (shi > bhi) bhi = shi;
    if (slo < 0) slo = 0;
    if (shi < 0) shi = 0;
  }
  return(max(abs(blo), abs(bhi)));
}

double tsearch(double lo, double hi)
{
  double mlo = (2*lo + hi) / 3, mhi = (lo + 2*hi) / 3;
  if (lo >= hi - 1e-13) return(lo);

  double elo = evaluate(mlo), ehi = evaluate(mhi);
  if (elo < ehi) return(tsearch(lo, mhi));
  else if (ehi < elo) return(tsearch(mlo, hi));
  else return(tsearch(mlo, mhi));
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
    scanf("%d", &array[i]);

  double best = tsearch(-1e6 - 1, 1e6 + 1);
  printf("%.15lf\n", evaluate(best));

  return(0);
}