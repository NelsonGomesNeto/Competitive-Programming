#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    lli a, b, c, n; scanf("%lld %lld %lld %lld", &a, &b, &c, &n);
    lli C = (n + a + b - 2*c) / 3;
    lli B = c + C - b;
    lli A = b + B - a;
    // printf("\t%lld %lld %lld\n", A, B, C);
    printf("%s\n", A >= 0 && B >= 0 && C >= 0 && (A + B + C == n) && a + A == b + B && b + B == c + C ? "YES" : "NO");
  }
  return 0;
}

/*
{
  A + B + C = n
  a + A = b + B = c + C;
  A = b + B - a;
  B = c + C - b;
  A = b + (c + C - b) - a

  b + (c + C - b) - a + (c + C - b) + C = n
  2c + 3C - a - b = n
  3C = n + a + b - 2c
  C = (n + a + b - 2c) / 3
}
*/