#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  2 * 11111111 % mod = 0
  (2 % mod * 1111111 % mod) % mod = 0

*/

int k;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &k);

    int mex = 0;
    for (int bit = 0; bit < 25; bit++)
      if (k & (1 << bit))
        mex = bit;

    int ans = k - (1 << max(0, (mex - 3)));
    printf("%d\n", ans);
  }
  return 0;
}