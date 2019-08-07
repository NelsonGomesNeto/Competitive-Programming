#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1000; int n, L, H;
const long double inf = 1e18, pi2 = acos(-1) / 2.0;
struct Wood
{
  long double xi, xf, yi, yf;
  void read() { scanf("%Lf %Lf %Lf", &yi, &xf, &yf); }
};
long double distance(long double x1, long double y1, long double x2, long double y2)
{
  return(sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)));
}
long double angle(long double x1, long double y1, long double x2, long double y2)
{
  // cos(theta) = <u, v> / (||u||*||v||)
  // theta = acos(<u, v> / (||u||*||v||))
  long double internProduct = x1 * x2 + y1 * y2;
  long double uNorm = sqrt(x1*x1 + y1*y1), vNorm = sqrt(x2*x2 + y2*y2);
  return(acos(internProduct / (uNorm * vNorm)));
}
Wood woods[maxN];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    scanf("%d %d", &L, &H);
    for (int i = 0; i < n; i ++)
    {
      woods[i].read();
      if (i & 1) woods[i].xi = L;
      else woods[i].xi = 0;
    }

    long double diameter = inf;
    for (int i = 0; i < n; i ++)
    {
      if (i & 1) diameter = min(diameter, woods[i].xf);
      else diameter = min(diameter, L - woods[i].xf);

      if (i < n - 1)
      {
        long double theta = angle(woods[i].xf - woods[i + 1].xf, woods[i].yf - woods[i + 1].yf, woods[i + 1].xf - woods[i + 1].xi, woods[i + 1].yf - woods[i + 1].yi);
        long double sine = sin(angle(woods[i].xf - woods[i + 1].xf, woods[i].yf - woods[i + 1].yf, woods[i + 1].xf - woods[i + 1].xi, woods[i + 1].yf - woods[i + 1].yi));
        if (theta <= pi2) sine = 1;
        long double dist = sine * distance(woods[i].xf, woods[i].yf, woods[i + 1].xf, woods[i + 1].yf);
        diameter = min(diameter, dist);
      }
    }
    printf("%.2Lf\n", diameter);
  }
  return(0);
}