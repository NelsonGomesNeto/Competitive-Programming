#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
int f[maxN], c[maxN];
lli minimum[maxN], maximum[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; ++i)
      scanf("%d", &f[i]);
    for (int i = 0; i < n; ++i)
      scanf("%d", &c[i]);

    sort(f, f+n);
    sort(c, c+n);

    vector<int> p1, p2;
    for (int i = 0; i < n; ++i)
      p1.push_back(i);
    p2 = p1;

    fill(minimum, minimum+n, LONG_LONG_MAX);
    fill(maximum, maximum+n, LONG_LONG_MIN);
    do
    {
      do
      {
        lli sum = 0;
        for (int i = 0; i < n; ++i)
        {
          sum += f[p1[i]] * c[p2[i]];
          minimum[i] = min(minimum[i], sum);
          maximum[i] = max(maximum[i], sum);
        }
      }
      while (next_permutation(p2.begin(), p2.end()));
    } while (next_permutation(p1.begin(), p1.end()));

    for (int i = 0; i < n; ++i)
      printf("%lld %lld\n", minimum[i], maximum[i]);
  }
  return 0;
}