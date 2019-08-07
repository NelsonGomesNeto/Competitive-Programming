#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli mod = 1e9 + 7;
int n, q;
set<vector<int>> all;
vector<int> arr;

bool valid(int k)
{
  int first[100], last[100];
  memset(last, -1, sizeof(last));
  memset(first, -1, sizeof(first));
  for (int i = 0; i < n; i ++) last[arr[i]] = i;
  for (int i = n - 1; i >= 0; i --) first[arr[i]] = i;

  for (int i = 2; i <= k; i ++)
    if (first[i] != -1 && first[i - 1] == -1)
      return(false);
    else if (first[i] != -1 && first[i - 1] > last[i])
      return(false);
  return(true);
}

void fill(int k, int i = 0)
{
  if (i == n)
  {
    if (valid(k)) all.insert(arr);
    return;
  }
  for (int j = 1; j <= k; j ++)
  {
    arr[i] = j;
    fill(k, i + 1);
  }
}

lli modPow(lli x, lli y)
{
  if (!y) return(1);
  lli ret = modPow(x, y >> 1);
  ret = (ret * ret) % mod; if (y & 1) ret = (ret * x) % mod;
  return(ret);
}

lli fat(lli n)
{
  if (n <= 1) return(1);
  return(n * fat(n - 1) % mod);
}

lli inv(lli n)
{
  return(modPow(n, mod - 2));
}

lli choose(lli n, lli k)
{
  return(fat(n) * inv(fat(k) * fat(n - k) % mod) % mod);
}

lli solve(lli k)
{
  lli ans = 0;
  for (lli t = 0; t < k; t ++)
  {
    ans = (mod + (ans + ((t & 1) ? -1LL : 1LL) * choose(n, t) * modPow(k - t, n) % mod) % mod) % mod;
  }
  return(ans);
}

int main()
{
  scanf("%d %d", &n, &q);

  while (q --)
  {
    int k; scanf("%d", &k);
    k = min(k, n);
    printf("%lld", solve(k));
    if (q) printf(" ");
    else printf("\n");
  }

  return(0);
}
// 1 2 3 4  5  6  7  8  9 10
// 2 3 5 7 11 13 17 19 23 29