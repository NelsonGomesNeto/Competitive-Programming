#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5;
int n; lli t;
lli a[maxN];

int main()
{
  while (~scanf("%d %lld", &n, &t))
  {
    lli sum = 0;
    for (int i = 0; i < n; ++i)
    {
      scanf("%lld", &a[i]);
      sum += a[i];
    }

    t %= sum;

    int song; lli at;
    for (int i = 0; i < n; ++i)
    {
      if (a[i] > t)
      {
        song = i; at = t;
        break;
      }
      t -= a[i];
    }
    printf("%d %lld\n", song + 1, at);
  }
  return 0;
}
