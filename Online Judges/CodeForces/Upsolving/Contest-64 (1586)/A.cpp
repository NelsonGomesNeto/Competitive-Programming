#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2, maxA = 2e2; int n;
int a[maxN];

const int maxX = 1e6;
bool notPrime[maxX + 1];
vector<int> primes;

int memo[maxN][maxN*maxA + 1], path[maxN][maxN*maxA + 1];
int solve(int i = 0, int sum = 0)
{
  if (i == n) return notPrime[sum] ? 0 : -1e6;
  int &ans = memo[i][sum], &p = path[i][sum];
  if (ans != -1) return ans;
  int notPut = solve(i + 1, sum), put = 1 + solve(i + 1, sum + a[i]);
  p = put > notPut;
  return ans = max(notPut, put);
}

int main()
{
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i <= maxX; i ++)
  {
    if (!notPrime[i]) primes.push_back(i);
    for (int j = 0; i*primes[j] <= maxX; j ++)
    {
      notPrime[i*primes[j]] = true;
      if (i % primes[j] == 0) break;
    }
  }

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    memset(memo, -1, sizeof(memo));
    memset(path, -1, sizeof(path));
    int ans = solve();
    printf("%d\n", ans);
    vector<int> res;
    for (int i = 0, sum = 0; i < n; i++)
      if (path[i][sum]) res.push_back(i), sum += a[i];
    for (int i = 0; i < res.size(); i++)
      printf("%d%c", res[i] + 1, i < res.size() - 1 ? ' ' : '\n');
  }
  return 0;
}
