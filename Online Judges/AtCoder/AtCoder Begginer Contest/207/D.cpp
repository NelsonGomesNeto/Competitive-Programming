#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const double pi = acos(-1);
const double eps = 1e-3;

const int maxN = 100; int n;
struct Point
{
  double x, y;
  void read() { scanf("%lf %lf", &x, &y); }
  double distance(Point &other) { return abs(x - other.x) + abs(y - other.y); }
  Point rotate(double angle)
  {
    // cos -sin | x
    // sin  cos | y
    double c = cos(angle), s = sin(angle);
    return Point{c*x - s*y, s*x + c*y};
  }
};
Point s[maxN], t[maxN], aux[maxN];
list<Point> tt;

double evalY(double angle, double x, double y)
{
  tt.clear();
  for (int i = 0; i < n; i++)
  {
    tt.push_back(t[i]);
    aux[i] = s[i].rotate(angle);
    aux[i].x += x;
    aux[i].y += y;
  }

  double total = 0;
  for (int i = 0; i < n; i++)
  {
    double minDist = 1e9; list<Point>::iterator bestIt;
    for (auto it = tt.begin(); it != tt.end(); it++)
    {
      double dist = aux[i].distance(*it);
      if (dist < minDist)
        minDist = dist, bestIt = it;
    }
    total += minDist;
    tt.erase(bestIt);
  }
  return total;
}
double evalX(double angle, double x)
{
  double lo = -30, hi = 30;
  while (abs(hi - lo) > eps)
  {
    double midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
    double elo = evalY(angle, x, lo), ehi = evalY(angle, x, hi);
    if (elo < ehi) hi = midhi;
    else lo = midlo;
  }
  double mid = (lo + hi) / 2;
  return evalY(angle, x, mid);
}
double evalAngle(double angle)
{
  double lo = -30, hi = 30;
  while (abs(hi - lo) > eps)
  {
    double midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
    double elo = evalX(angle, lo), ehi = evalX(angle, hi);
    if (elo < ehi) hi = midhi;
    else lo = midlo;
  }
  double mid = (lo + hi) / 2;
  return evalX(angle, mid);
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++) s[i].read();
    for (int i = 0; i < n; i++) t[i].read();

    bool can = false;
    for (int i = 0; i <= 16; i++)
      if (evalAngle(pi / 8 * i) < 1)
        can = true;
    printf("%s\n", can ? "Yes" : "No");

    // double lo = 0, hi = 2*pi;
    // while (abs(hi - lo) > eps)
    // {
    //   double midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
    //   double elo = evalAngle(lo), ehi = evalAngle(hi);
    //   if (elo < ehi) hi = midhi;
    //   else lo = midlo;
    // }

    // double mid = (lo + hi) / 2;
    // // double mid = pi / 2;
    // printf("%lf %lf\n", mid, evalAngle(mid));
  }
  return 0;
}