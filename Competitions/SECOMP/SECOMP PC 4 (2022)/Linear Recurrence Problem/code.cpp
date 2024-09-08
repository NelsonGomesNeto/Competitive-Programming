#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int f(const vector<int>& a, int n)
{
  if (n <= 3) return a[n];
  return 9 * f(a, n - 1) + 2 * f(a, n - 2) - 5 * f(a, n - 3) + f(a, n - 4);
}

const int maxN = 10;
int n, a, b, c, d;

int main()
{
  while (~scanf("%d %d %d %d %d", &a, &b, &c, &d, &n))
  {
    int ans = f({a, b, c, d}, n);
    printf("%lld\n", ans);
  }
  return 0;
}
