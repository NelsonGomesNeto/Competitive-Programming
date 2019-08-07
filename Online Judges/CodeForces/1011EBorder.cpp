#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli gdc(lli a, lli b)
{
  if (!b) return(a);
  return(gcd(b, a % b));
}

int main()
{
  int n, k; scanf("%d %d", &n, &k);
  int a[n]; for (int i = 0; i < n; i ++) scanf("%d", &a[i]);

  int rem[k]; memset(rem, 0, sizeof(rem));
  for (int i = 0; i < n; i ++)
    rem[a[i] % k] = 1;

  vector<int> divi; for (int i = 0; i < k; i ++) if (rem[i]) divi.push_back(i);

  int g = divi[0];
  for (int i = 1; i < divi.size(); i ++)
    g = gcd(g, divi[i]);
  divi.push_back(g);

    for (lli j = g, kk = 0; kk < 2; j += g)
    {
      j %= k;
      if (j == g) kk ++;
      rem[j] = 1;
    }

  // for (int i = 0; i < divi.size(); i ++)
  //   if (divi[i])
  //     for (int j = divi[i]; j < k; j += divi[i])
  //       rem[j] = 1;

  divi.clear(); for (int i = 0; i < k; i ++) if (rem[i]) divi.push_back(i);

  printf("%d\n", divi.size());
  for (int i = 0; i < divi.size(); i ++)
    printf("%d%c", divi[i], i < divi.size() - 1 ? ' ' : '\n');

  return(0);
}
