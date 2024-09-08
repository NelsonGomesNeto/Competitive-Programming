#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int gcd(int a, int b)
{
  return b == 0 ? a : gcd(b, a % b);
}

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    int n; scanf("%d", &n);
    int a[n]; for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    int g = a[0]; for (int i = 1; i < n; i++) g = gcd(g, a[i]);
    printf("%s\n", g == 1 ? "YES" : "NO");
  }
  return 0;
}