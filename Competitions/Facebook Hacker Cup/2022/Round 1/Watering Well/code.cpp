#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
Euclidean Distance:
(x1, y1) (x2, y2)
sqrt((x1 - x2)^2 + (y1 - y2)^2)

squared Euclidean Distance:
(x1 - x2)^2 + (y1 - y2)^2

(a - b)^2
a^2 - 2*a*b + b^2

incovenience of a well:
sum ||p - ti||^2
sum (p.x - ti.x)^2 + (p.y - ti.y)^2
sum (p.x^2 - 2*p.x*ti.x + ti.x^2) + (p.y^2 - 2*p.y*ti.y + ti.y^2)
n*(p.x^2 + p.y^2) + sum(ti.x^2) + sum(ti.y^2) - sum(2*p.x*ti.x) - sum(2*p.y*ti.y)
n*(p.x^2 + p.y^2) + sum(ti.x^2) + sum(ti.y^2) - 2*p.x*sum(ti.x) - 2*p.y*sum(ti.y)
*/

void fastReadInt(lli &x)
{
  bool neg = false;
  int c = ' ';
  x = 0;
  while (c != '-' && (c < '0' || c > '9'))
    c = getchar();
 
  if (c == '-')
    neg = true, c = getchar();
 
  for ( ; (c > 47 && c < 58); c = getchar())
    x = (x<<1) + (x<<3) + c - 48;
  if (neg)
    x *=-1;
}

const int maxN = 5e5; int n, q;
const lli mod = 1e9 + 7;
struct Point
{
  lli x, y;
  void read() { fastReadInt(x); fastReadInt(y); }
};
Point trees[maxN], wells[maxN];

int main()
{
  int testCases; scanf("%d", &testCases);
  for (int testCase = 1; testCase <= testCases; ++testCase)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) trees[i].read();

    scanf("%d", &q);
    for (int i = 0; i < q; ++i) wells[i].read();

    // n*(p.x^2 + p.y^2) + sum(ti.x^2) + sum(ti.y^2) - 2*p.x*sum(ti.x) - 2*p.y*sum(ti.y)
    lli sumTreeX = 0, sumTreeY = 0;
    lli sumTreeXSquared = 0, sumTreeYSquared = 0;
    for (int i = 0; i < n; ++i)
    {
      sumTreeXSquared = (sumTreeXSquared + trees[i].x * trees[i].x % mod) % mod;
      sumTreeYSquared = (sumTreeYSquared + trees[i].y * trees[i].y % mod) % mod;
      sumTreeX = (sumTreeX + trees[i].x) % mod;
      sumTreeY = (sumTreeY + trees[i].y) % mod;
    }
    lli ans = 0;
    for (int i = 0; i < q; ++i)
    {
      ans = (ans
              + (lli)n*((wells[i].x*wells[i].x % mod + wells[i].y*wells[i].y % mod) % mod) % mod
              + sumTreeXSquared
              + sumTreeYSquared
              - 2LL * wells[i].x % mod * sumTreeX % mod
              - 2LL * wells[i].y % mod * sumTreeY % mod
            ) % mod;
      ans = (ans + mod) % mod;
    }
    printf("Case #%d: %lld\n", testCase, ans);
  }
  return 0;
}
