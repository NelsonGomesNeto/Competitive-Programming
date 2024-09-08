#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    int n; scanf("%d", &n);
    int a[n]; for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    int rounds = 1, alice = 0, aa = 0, bob = 0, bb = 0;
    for (int l = 0, r = n - 1, turn = 0; ; rounds++, turn = !turn)
    {
      if (!turn)
      {
        aa = 0;
        while (l <= r && aa <= bb)
        {
          aa += a[l];
          alice += a[l++];
        }
      }
      else
      {
        bb = 0;
        while (l <= r && bb <= aa)
        {
          bb += a[r];
          bob += a[r--];
        }
      }
      if (l > r) break;
    }
    printf("%d %d %d\n", rounds, alice, bob);
  }
  return 0;
}
