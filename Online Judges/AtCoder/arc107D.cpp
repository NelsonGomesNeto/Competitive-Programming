#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 998244353;

// maximum divisor will be: 2^11 = 2048 (so make it the common divisor)
const int optionsSize = 30;
const lli maxDiv = 1LL << (optionsSize - 1);

const int maxN = 3e3; const lli maxK = 3000LL * (1 << (optionsSize - 1));
int n; lli k;

// 3e3 * 12 * 3000 * 2048
unordered_map<lli, lli> memo[maxN][optionsSize];
lli solve(int i = 0, int p = optionsSize - 1, lli sum = 0)
{
  if (i == n) return sum == k;
  if (sum + (n - i) > k || sum + (n - i)*(1 << p) < k) return 0;
  if (memo[i][p].count(sum)) return memo[i][p][sum];
  // lli &ans = memo[i][p];
  // if (ans != -1) return ans;

  lli ans = 0;
  for (int j = 0; j <= p; j++)
    ans = (ans + solve(i + 1, j, sum + (1 << j))) % mod;
  return memo[i][p][sum] = ans;
}

int main()
{
  while (scanf("%d %lld", &n, &k) != EOF)
  {
    k *= maxDiv;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < optionsSize; j++)
        memo[i][j].clear();
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}