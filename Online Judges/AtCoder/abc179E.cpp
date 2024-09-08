#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli maxN = 1e10, maxX = 1e5 + 2; lli n, x, m;
map<lli, int> curr;
lli acc[maxX];

int main()
{
  while (scanf("%lld %lld %lld", &n, &x, &m) != EOF)
  {
    lli a = x;
    lli i;
    curr.clear();
    acc[0] = 0;
    for (i = 1; i <= n; i++)
    {
      DEBUG if (i < 10) printf("\t\t%lld %lld\n", i, a);
      if (curr.count(a)) break;
      curr[a] = i;
      acc[i + 1] = acc[i] + a;
      a = a * a % m;
    }

    if (i > n) printf("%lld\n", acc[n + 1]);
    else
    {
      lli first = curr[a];
      DEBUG printf("\t%lld %lld %lld\n", first, i, a);
      DEBUG printf("\t%lld | %lld %lld | %lld\n", acc[first], acc[i], acc[i] - acc[first], n - i);
      lli ans = acc[first], blockSize = i - first;
      lli fits = (n - first + 1) / blockSize;
      lli lefts = (n - first + 1) % blockSize;
      ans += (acc[i] - acc[first]) * fits; // full blocks sum
      ans += acc[first + lefts] - acc[first];
      lli target = 492443256176507 - ans;
      // printf("\t%lld | %lld\n", target, lefts);
      // for (lli j = first; j <= i; j++)
      //   if (acc[j] - acc[first] == target)
      //     printf("\tfound %lld\n", j);
      printf("%lld\n", ans);
    }
  }
  return 0;
}