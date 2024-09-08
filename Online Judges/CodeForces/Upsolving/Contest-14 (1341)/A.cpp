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
    int minimum = (a - b) * n, maximum = (a + b) * n;
    printf("%s\n", inside(c - d, minimum, maximum) || inside(c + d, minimum, maximum) || inside(minimum, c - d, c + d) || inside(maximum, c - d, c + d) ? "YES" : "NO");
  }
  return 0;
}
