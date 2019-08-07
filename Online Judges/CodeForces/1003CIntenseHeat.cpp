#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, k; scanf("%d %d", &n, &k);
  int a[n]; for (int i = 0; i < n; i ++) scanf("%d", &a[i]);

  long double term[n + 1]; term[0] = 0;
  for (int i = 0; i < n; i ++) term[i + 1] = term[i] + a[i];

  long double mean = 0;
  for (int j = k; j <= n; j ++)
    for (int i = j; i <= n; i ++)
      mean = max(mean, (long double) (term[i] - term[i - j]) / j);

  printf("%.15Lf\n", mean);

  return(0);
}