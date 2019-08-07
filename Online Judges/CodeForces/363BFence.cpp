#include <bits/stdc++.h>
using namespace std;
long long int inf = 1e12;

int main()
{
  int n, k; scanf("%d %d", &n, &k);
  int fence[n];
  for (int i = 0; i < n; i ++) scanf("%d", &fence[i]);

  long long int accumulated[n]; accumulated[0] = fence[0];
  for (int i = 1; i < n; i ++)
    accumulated[i] = accumulated[i - 1] + fence[i];

  long long int ans = inf, pos = 0;
  for (int i = 0; i < n - k + 1; i ++)
    if (accumulated[i + k - 1] - (i > 0 ? accumulated[i - 1] : 0) < ans)
    {
      ans = accumulated[i + k - 1] - (i > 0 ? accumulated[i - 1] : 0);
      pos = i + 1;
    }

  printf("%lld\n", pos);

  return(0);
}