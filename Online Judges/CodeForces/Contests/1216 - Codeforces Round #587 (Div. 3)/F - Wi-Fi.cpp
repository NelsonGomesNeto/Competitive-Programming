#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5; int n, k;
const lli inf = 1e16;
int hasRouter[maxN + 2], rightRouter[maxN + 2];
lli memo[maxN + 2];

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    for (int i = 1; i <= n; i ++)
      scanf("%1d", &hasRouter[i]);

    rightRouter[n + 1] = 1e9;
    for (int i = n; i > 0; i --)
      rightRouter[i] = hasRouter[i] ? i : rightRouter[i + 1];

    for (int i = 1; i <= n; i ++)
    {
      memo[i] = i + memo[i - 1];
      int closest = rightRouter[max(1, i - k)];
      if (closest <= i + k)
        memo[i] = min(memo[i], memo[max(1, closest - k) - 1] + closest);
    }

    printf("%lld\n", memo[n]);
  }
  return(0);
}
