#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  polygon area = 1 / 2 * diagMult(points)

  diagMult = (x1*y2 + x2*y3 + ... + xn*y1) - (y1*x2 + y2*x3 + ... + yn*x1)

  x1 = y1 = 0 -> x1*y2 = xn*y1 = y1*x2 = yn*x1 = 0
  At 2-th step, I will add:
    x2*y3 - y2*x3
    x3*y4 - y3*x4

  So I want diagMult to eq A
*/

const int maxN = 1e3; int n; lli A;
int delta = 10;

// x1 = y1 = 0
string pointsAns = "";
int solve(int i = 1, lli total = 0, lli prvX = 0, lli prvY = 0)
{
  if (total > A) return 0;
  DEBUG printf("\t%d - %lld %lld - %lld %lld\n", i, total, A, prvX, prvY);
  if (i == n) return total == A;

  if (i == 1)
  {
    for (lli x = 1; x <= 2; x++)
      for (lli y = 1; y <= 2; y++)
        if (solve(i + 1, total, x, y))
        {
          pointsAns += to_string(x) + " " + to_string(y) + "\n";
          return true;
        }
  }
  else if (i < (n >> 1))
  {
    lli left = A - total;
    // prvX*y - prvY*x <= left
    // x >= -(left - prvX*y) / prvY
    for (lli y = prvY; y <= prvY + delta; y++)
    {
      if (i != n - 1 && y == 0) continue;
      lli baseX = (-prvX*y + left) / prvY + ((-prvX*y + left) % prvY != 0);
      DEBUG printf("\t\t%lld - %lld\n", y, baseX);
      for (lli x = baseX; x <= baseX + delta; x++)
        if (x >= prvX && solve(i + 1, total + -(prvX*y - prvY*x), x, y))
        {
          pointsAns += to_string(x) + " " + to_string(y) + "\n";
          return true;
        }
    }
  }
  else
  {
    lli left = A - total;
    // prvX*y - prvY*x <= left
    // x >= -(left - prvX*y) / prvY
    for (lli y = prvY; y >= prvY - 2; y--)
    {
      if (i != n - 1 && y == 0) continue;
      lli baseX = (-prvX*y + left) / prvY + ((-prvX*y + left) % prvY != 0);
      DEBUG printf("\t\t%lld %lld - %lld\n", prvY, y, baseX);
      for (lli x = baseX; x <= baseX + delta; x++)
      {
        if ((x >= prvX || (x >= 0 && y <= 0)) && (x != prvX || y != prvY) && (x || y) && solve(i + 1, total + -(prvX*y - prvY*x), x, y))
        {
          pointsAns += to_string(x) + " " + to_string(y) + "\n";
          return true;
        }
      }
    }
  }
  return false;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %lld", &n, &A);
    delta = min(100, (int)A);
    pointsAns = "0 0\n";
    int ans = solve();
    if (!ans) printf("Case #%d: IMPOSSIBLE\n", tt);
    else
    {
      printf("Case #%d: POSSIBLE\n", tt);
      printf("%s", pointsAns.c_str());
    }
  }
  return 0;
}