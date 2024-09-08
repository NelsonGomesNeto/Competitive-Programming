#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  set<lli> left;
  for (int i = 1; i <= 3000; i++)
    left.insert(i);
  while (!left.empty())
  {
    int ii, jj, kk = -1;
    for (auto i: left)
    {
      for (auto j: left)
      {
        for (auto k: left)
          if (i != j && j != k && i != k)
            if (((i ^ j) ^ k) == 0)
            {
              printf("%lld %lld %lld\n", i, j, k);
              kk = k;
              break;
            }
        if (kk != -1)
        {
          jj = j;
          break;
        }
      }
      if (kk != -1)
      {
        ii = i;
        break;
      }
    }
    left.erase(ii), left.erase(jj), left.erase(kk);
  }

  int t; scanf("%d", &t);
  while (t--)
  {
    lli n; scanf("%lld", &n);
    // p
  }
  return 0;
}
