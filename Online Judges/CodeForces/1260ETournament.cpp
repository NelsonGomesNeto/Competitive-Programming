#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  Notice that your friend will have log2(n) matches, always. So you have to
  bribe at most log2(n) competidors.

  Let's reverse the competidors array, it will be easier to calculate stuff

  For each competidor i:
    If i is your friend:
      he will defeat the rest of the competidors
    Else:
      You may bribe him or not
        Notice that you shouldn't bribe him if you've already bribed log2(n) competidors

      Notice that bribeing will guarantee some wins:
        1 bribed competidors accounts for at most 2^(log(n) - 1) wins
        2 bribed: the same as above + 2^(log(n) - 2)
        ...
        k bribed: 2^(log(n) - 1) + 2^(log(n) - 2) + ... + 2^(log(n) - k)
        Let's denote this as defeated[k]

      If defeated[k] >= competidors so far (<= i):
        You can leave this guy to be defeated by one of your bribed competidors
        So, don't bribe him

  Useing dynamic programming:
    memo[k][i] = minimum cost of winning all competidors from i to n having k bribed
    memo[k][i] = min{
                      solve(k + 1, i + 1) + cost[i], if k < matches;
                      solve(k, i + 1), if defeated[k] >= (i+1)
                    }
*/

const int maxN = 1 << 18, maxLog = 18 + 1; int n, f, matches;
const lli inf = 1e16;
lli a[maxN];
int defeated[maxLog];

lli memo[maxLog][maxN];
lli solve(int bribed = 0, int i = 0)
{
  if (a[i] == -1) return 0;
  if (memo[bribed][i] != -1) return memo[bribed][i];

  lli ans = inf;
  if (bribed < matches)
    ans = solve(bribed + 1, i + 1) + a[i];
  if (defeated[bribed] >= i + 1)
    ans = min(ans, solve(bribed, i + 1));

  return memo[bribed][i] = ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    matches = log2(n);
    for (int i = 0; i < n; i ++)
      scanf("%lld", &a[i]);
    reverse(a, a+n);

    for (int i = 1, x = n >> 1; i <= matches; i ++, x >>= 1)
      defeated[i] = defeated[i - 1] + x;

    memset(memo, -1, sizeof(memo));
    printf("%lld\n", solve());
  }
  return 0;
}
