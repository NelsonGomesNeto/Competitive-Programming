#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n[3];
const lli inf = LONG_LONG_MAX;
lli w[3][maxN];

lli dist(lli a, lli b)
{
  return (a - b)*(a - b);
}
lli evaluate(lli rw, lli gw, lli bw)
{
  return dist(rw, gw) + dist(rw, bw) + dist(gw, bw);
}
lli ternarySearch2(lli rw, int pos)
{
  lli gw = w[1][pos];
  int lo = 0, hi = n[2] - 1;
  while (lo < hi - 3)
  {
    int midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
    int elo = evaluate(rw, gw, w[2][midlo]), ehi = evaluate(rw, gw, w[2][midhi]);
    if (elo <= ehi) hi = midhi;
    else lo = midlo;
  }
  lli ans = evaluate(rw, gw, w[2][lo++]);
  while (lo <= hi) ans = min(ans, evaluate(rw, gw, w[2][lo++]));
  return ans;
}
lli ternarySearch(int pos)
{
  lli rw = w[0][pos];
  int lo = 0, hi = n[1] - 1;
  while (lo < hi - 3)
  {
    int midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
    int elo = ternarySearch2(rw, midlo), ehi = ternarySearch2(rw, midhi);
    if (elo <= ehi) hi = midhi;
    else lo = midlo;
  }
  lli ans = ternarySearch2(rw, lo++);
  while (lo <= hi) ans = min(ans, ternarySearch2(rw, lo++));
  return ans;
}

int binarySearch(lli value, int k, bool upperBound)
{
  int lo = 0, hi = n[k] - 1;
  while (lo < hi)
  {
    int mid = (lo + hi + upperBound) >> 1;
    if (upperBound)
    {
      if (w[k][mid] <= value) lo = mid;
      else hi = mid - 1;
    }
    else
    {
      if (w[k][mid] >= value) hi = mid;
      else lo = mid + 1;
    }
  }
  return lo;
}

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    for (int i = 0; i < 3; i++) scanf("%d", &n[i]);
    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < n[i]; j++)
        scanf("%lld", &w[i][j]);
      sort(w[i], w[i]+n[i]);
    }

    lli ans = inf;
    // for (int j = 0; j < n[0]; j++)
    //   ans = min(ans, ternarySearch(j));

    for (int j = 0; j < n[0]; j++)
    {
      int after = binarySearch(w[0][j], 1, false), before = binarySearch(w[0][j], 1, true);
      ans = min({ans, ternarySearch2(w[0][j], after), ternarySearch2(w[0][j], before)});
    }

    vector<int> p = {0, 1, 2};
    do
    {
      for (int j = 0; j < n[p[0]]; j++)
      {
        int after = binarySearch(w[p[0]][j], p[1], false), before = binarySearch(w[p[0]][j], p[1], true);
        int afterAfter = binarySearch((w[p[0]][j] + w[p[1]][after]) >> 1LL, p[2], false), afterBefore = binarySearch((w[p[0]][j] + w[p[1]][after]) >> 1LL, p[2], true);
        int beforeAfter = binarySearch((w[p[0]][j] + w[p[1]][before]) >> 1LL, p[2], false), beforeBefore = binarySearch((w[p[0]][j] + w[p[1]][before]) >> 1LL, p[2], true);

        int aa[2] = {after, before}, bb[4] = {afterAfter, afterBefore, beforeAfter, beforeBefore};
        for (int k = 0; k < 2; k++)
          for (int l = 0; l < 4; l++)
            ans = min(ans, evaluate(w[p[0]][j], w[p[1]][aa[k]], w[p[2]][bb[l]]));
      }
    } while (next_permutation(p.begin(), p.end()));

    printf("%lld\n", ans);
  }
  return 0;
}
