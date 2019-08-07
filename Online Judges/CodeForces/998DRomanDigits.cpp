#include <bits/stdc++.h>
using namespace std;
#define lli long long int
int d[4] = {1, 5, 10, 50};

void romanDigits(set<int>& numbers, int i, int now)
{
  if (i == -1)
  {
    numbers.insert(now);
    return;
  }
  for (int k = 0; k < 4; k ++)
    romanDigits(numbers, i - 1, now + d[k]);
}

lli apSum(lli a, lli b, lli r)
{
  return((long double) (a + b) / 2 * (b - a + 1) * r);
}

int main()
{
  lli ans[13] = {0, 4, 10, 20, 35, 56, 83, 116, 155, 198, 244, 292, 341};
  lli n; scanf("%lld", &n);

  if (n <= 12) printf("%lld\n", ans[n]);
  else printf("%lld\n", ans[12] + (lli) 49 * (n - 12));
  return(0);
}
/*
4 6
10 10
20 10
35 15
56 21
83 27
116 33
155 39
198 43
244 46
292 48
341 49 12
390 49 13
439 49 14
488 49 15
*/