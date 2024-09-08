#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3, maxM = 2e3; int n, m, k;
struct Segment
{
  int lo, hi;
  void read() { scanf("%d %d", &lo, &hi); lo--, hi--; }
  int intersection(int olo, int ohi)
  {
    return max(0, min(hi, ohi) - max(lo, olo) + 1);
  }
  double intersection(double olo, double ohi)
  {
    return max((double)0, min((double)hi, ohi) - max((double)lo, olo) + 1);
  }
};
Segment competidors[maxM];

double eval(double j)
{
  double ans = 0;
  for (double i = 0; i + k - 1 < n; i++)
  {
    double sum = 0;
    for (int c = 0; c < m; c++)
      sum += max(competidors[c].intersection(i, i + k - 1), competidors[c].intersection(j, j + k - 1));
    ans = max(ans, sum);
  }
  return ans;
}
const int delta = 200;
int ternarySearch(double lo, double hi)
{
  while (lo < hi - delta)
  {
    double midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
    double elo = eval(midlo), ehi = eval(midhi);
    if (elo > ehi) lo = midlo - 1;
    else if (ehi > elo) hi = midhi + 1;
    else lo = midlo - 1, hi = midhi + 1;
  }
  double ans = 0;
  lo = max((double)0, floor(lo));
  hi = min((double)(n - k), ceil(hi));
  while (lo <= hi) ans = max(ans, eval(lo++));
  return round(ans);
}

int main()
{
  while (scanf("%d %d %d", &n, &m, &k) != EOF)
  {
    for (int i = 0; i < m; i++)
      competidors[i].read();

    int ans = ternarySearch(0, n - k);
    // for (int i = 0; i + k - 1 < n; i++)
    // {
    //   // for (int j = i; j + k - 1 < n; j++)
    //   // {
    //   //   int sum = 0;
    //   //   for (int c = 0; c < m; c++)
    //   //     sum += max(competidors[c].intersection(i, i + k - 1), competidors[c].intersection(j, j + k - 1));
    //   //   printf("\t%d - %d - %d\n", i, j, sum);
    //   //   ans = max(ans, sum);
    //   // }
    //   // printf("ended %d ----------------\n", i);
    // }
    printf("%d\n", ans);
  }
  return 0;
}
