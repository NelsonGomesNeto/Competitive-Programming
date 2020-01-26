#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5;

int main()
{
  lli h; int n;
  while (scanf("%lld %d", &h, &n) != EOF)
  {
    lli s = 0;
    for (int i = 0; i < n; i ++)
    {
      lli a; scanf("%lld", &a);
      s += a;
    }
    printf("%s\n", s >= h ? "Yes" : "No");
  }
  return 0;
}