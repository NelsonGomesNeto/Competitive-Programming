#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  You will have to select a contiguous subarray, which can be:
  [] (empty)
  a ax a (multiplies just a subarray inside the selected subarray)
  ax a (same as above, but the inside extends to the beginning)
  a ax (same as above, but the inside extends to the end)
  ax (same as above, but the inside extends to both ends)
  a (same as above, but with no inside subarrays)

  Same knapsack idea, just that you have 4 possible states and more options:
  state 0: haven't started any of them
    can go to: 0, 1, 2, 3, end
  state 1: started an "a" (the left part of it)
    can go to: 1, 2, 3, end
  state 2: started an "ax"
    can go to: 2, 3, end
  state 3: stated an "a" (the right part of it)
    can go to: 3, end

  the answer will be the maximum, just like the knapsack problem
*/

const int maxN = 3e5; int n;
lli a[maxN], ax[maxN], x;

lli memo[maxN][4];
lli solve(int i = 0, int state = 0)
{
  if (i == n || state == 4) return(0);
  if (memo[i][state] == -1)
  {
    lli ans = 0;
    if (state == 0) ans = max({ans, solve(i + 1, 0), a[i] + solve(i + 1, 1), ax[i] + solve(i + 1, 2)});
    if (state == 1) ans = max({ans, a[i] + solve(i + 1, 1), ax[i] + solve(i + 1, 2), solve(i + 1, 4)});
    if (state == 2) ans = max({ans, ax[i] + solve(i + 1, 2), a[i] + solve(i + 1, 3), solve(i + 1, 4)});
    if (state == 3) ans = max({ans, a[i] + solve(i + 1, 3), solve(i + 1, 4)});
    memo[i][state] = ans;
  }
  return(memo[i][state]);
}

int main()
{
  scanf("%d %lld", &n, &x);
  for (int i = 0; i < n; i ++)
  {
    scanf("%lld", &a[i]);
    ax[i] = a[i] * x;
  }

  for (int i = 0; i < n; i ++)
  {
    if (i)
      for (int j = 0; j < 4; j ++)
        for (int k = j; k < 4; k ++)
          memo[i][j] = max(memo[i][j], memo[i - 1][k]);
    memo[i][1] += a[i];
    memo[i][2] += ax[i];
    memo[i][3] += a[i];
  }
  printf("%lld\n", max({memo[n - 1][0], memo[n - 1][1], memo[n - 1][2], memo[n - 1][3]}));
  // memset(memo, -1, sizeof(memo));
  // lli ans = solve();
  // printf("%lld\n", ans);

  return(0);
}