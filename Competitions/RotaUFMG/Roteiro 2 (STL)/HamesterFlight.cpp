#include <bits/stdc++.h>
double pi = atan(1)*4;
double v0, k1, k2;

double xf(double ang)
{
  return(-2.0*(v0*v0*cos(ang)*sin(ang))/(-10.0));
}

double ymax(double ang)
{
  return(-(v0*sin(ang))*(v0*sin(ang))/(2.0*-10));
}

double evaluate(double ang)
{
  return(xf(ang)*k1 + ymax(ang)*k2);
}

double tSearch(double lo, double hi)
{
  //printf("%lf %lf\n", lo, hi);
  double mlo = (2*lo + hi) / 3, mhi = (lo + 2*hi) / 3;
  if (lo >= hi - 1e-7) return(lo);
  double elo = evaluate(mlo), ehi = evaluate(mhi);
  if (elo > ehi) return(tSearch(lo, mhi));
  else if (ehi > elo) return(tSearch(mlo, hi));
  else return(tSearch(mlo, mhi));
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%lf %lf %lf", &v0, &k1, &k2);
    double angle = tSearch(0, pi/2);
    printf("%.3lf %.3lf\n", angle, evaluate(angle));
  }
  return(0);
}