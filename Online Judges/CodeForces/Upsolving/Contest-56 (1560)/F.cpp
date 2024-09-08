#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e9; lli n; int k;
vector<int> ndigits;

int memo[11][2][2][1 << 10];
int path[11][2][2][1 << 10];
int solve(int i = 0, bool equal = true, bool started = false, int mask = 0)
{
  if (__builtin_popcount(mask) > k) return 0;
  if (i == ndigits.size()) return started;
  int &ans = memo[i][equal][started][mask];
  if (ans != -1) return ans;

  int &p = path[i][equal][started][mask];
  ans = 0;
  for (int d = equal ? ndigits[i] : 0; d <= 9; d++)
  {
    ans = solve(i + 1, equal & (d == ndigits[i]), started | (d != 0), started | (d != 0) ? mask | (1 << d) : mask);
    if (ans)
    {
      p = d;
      break;
    }
  }
  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%lld %d", &n, &k);

    ndigits.clear();
    int aux = n;
    while (aux)
    {
      ndigits.push_back(aux % 10);
      aux /= 10;
    }
    while (ndigits.size() < 10) ndigits.push_back(0);
    reverse(ndigits.begin(), ndigits.end());

    memset(memo, -1, sizeof(memo));
    solve();

    vector<int> ans;
    for (int i = 0, equal = 1, started = 0, mask = 0; i < ndigits.size(); i++)
    {
      int d = path[i][equal][started][mask];
      equal &= d == ndigits[i];
      started |= d != 0;
      if (started)
      {
        mask |= (1 << d);
        ans.push_back(d);
      }
    }

    for (int d: ans) printf("%d", d);
    printf("\n");
  }
  return 0;
}
