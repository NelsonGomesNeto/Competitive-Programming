#include <bits/stdc++.h>
#define lli unsigned long long int
using namespace std;
int dc[5] = {1, 5, 10, 25, 50};

int main()
{
  lli dp[(int) 3e4 + 1]; memset(dp, 0, sizeof(dp)); dp[0] = 1;
  for (int j = 0; j < 5; j ++)
    for (int i = 1; i <= 3e4; i ++)
      if (i - dc[j] >= 0)
        dp[i] += dp[i - dc[j]];

  int n;
  while (scanf("%d", &n) != EOF)
  {
    if (dp[n] - 1) printf("There are %llu ways to produce %d cents change.\n", dp[n], n);
    else printf("There is only 1 way to produce %d cents change.\n", n);
  }
  return(0);
}
