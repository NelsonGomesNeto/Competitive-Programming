#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n, k;
const lli mod = 1e9 + 7;
vector<lli> planes;
vector<lli> nextPlanes;

int main()
{
  int t;
  while (~scanf("%d", &t))
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d %d", &n, &k);

      // 0 is infinte to the left and n + 1 is infinite to the right
      planes.clear();
      planes.resize(n + 2, 0);
      nextPlanes.clear();
      nextPlanes.resize(n + 2, 0);
      planes[0] = 1;
      lli ans = 0;
      for (int age = k, direction = 0; age >= 1; age--)
      {
        fill(nextPlanes.begin(), nextPlanes.end(), 0);

        lli curr = 0;
        if (direction == 0) // left -> right
        {
          for (int i = 0; i < n; i++)
          {
            curr = (curr + planes[i]) % mod;
            // if (curr)
            nextPlanes[i] = (nextPlanes[i] + curr) % mod;
          }
        }
        else
        {
          for (int i = n; i >= 0; i--)
          {
            curr = (curr + planes[i]) % mod;
            // if (curr)
            if (i)
              nextPlanes[i] = (nextPlanes[i] + curr) % mod;
          }
        }
        DEBUG printf("\t%d %lld\n", age, curr);
        ans = (ans + curr) % mod;

        planes = nextPlanes;
        direction = !direction;
      }
      printf("%lld\n", ans);
    }
  return 0;
}
