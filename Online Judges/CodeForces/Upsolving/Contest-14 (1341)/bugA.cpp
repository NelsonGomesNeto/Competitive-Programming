#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

bool inside(int a, int lo, int hi)
{
  return a >= lo && a <= hi;
}

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    int n, a, b, c, d; scanf("%d %d %d %d %d", &n, &a, &b, &c, &d);
    printf("%s\n", c + d >= n * (a - b) && c - d <= n * (a + b) ? "YES" : "NO");
  }
  return 0;
}
