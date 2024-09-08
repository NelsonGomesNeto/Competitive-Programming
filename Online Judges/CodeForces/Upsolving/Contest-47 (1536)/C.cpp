#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e5; int n;
char s[maxN + 1];
int accd[maxN + 1], acck[maxN + 1];
map<pair<int, int>, vector<int>> pos;
int ans[maxN];

void solve(int i = 0, int currd = 0, int currk = 0, int now = 1)
{
  if (i) ans[i - 1] = max(ans[i - 1], now);
  if (i == n) return;

  int tot = -1e6;
  int targetd = accd[i] + currd;
  int targetk = acck[i] + currk;

  auto dk = make_pair(targetd, targetk);
  if (dk.first && dk.second)
  {
    int g = gcd(dk.first, dk.second);
    dk.first /= g, dk.second /= g;
  }
  if (pos.count(dk))
  {
    auto &hehe = pos[dk];
    auto it = upper_bound(hehe.begin(), hehe.end(), i);
    if (it != hehe.end())
      solve(*it, currd, currk, now + 1);
  }
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    pos.clear();

    scanf("%d", &n);
    scanf(" %s", s);

    for (int i = 0; i < n; i++) ans[i] = 1;

    // pos[make_pair(0, 0)].push_back(0);
    for (int i = 0, d = 0, k = 0; i < n; i++)
    {
      accd[i + 1] = accd[i] + (s[i] == 'D');
      acck[i + 1] = acck[i] + (s[i] == 'K');
      auto p = make_pair(accd[i + 1], acck[i + 1]);
      if (p.first && p.second)
      {
        int g = gcd(p.first, p.second);
        p.first /= g, p.second /= g;
      }
      else
        p.first = p.second = 0;
      pos[p].push_back(i + 1);
      ans[i] = max(ans[i], (int)pos[p].size());
    }

    // for (int i = 0; i < n; i++)
    //   solve(i + 1, accd[i + 1], acck[i + 1]);

    for (int i = 0; i < n; i++)
      printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}
