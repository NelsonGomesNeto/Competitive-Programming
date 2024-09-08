#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
int n, m;
int a[maxN];

int cnt[maxN];
bool has[maxN];

bool add(int i)
{
  return ++cnt[a[i]] == 1;
}
bool isRequired(int i)
{
  return cnt[a[i]] == 1;
}
void remove(int i)
{
  --cnt[a[i]];
}

vector<int> solve(int i = 0, vector<int> curr = {}, set<int> has = {})
{
  if (has.size() == m) return curr;
  if (i == n) return {m + 1};

  vector<int> ans = solve(i + 1, curr, has);
  if (!has.count(a[i]))
  {
    curr.push_back(a[i]);
    has.insert(a[i]);
    ans = min(ans, solve(i + 1, curr, has));
  }

  return ans;
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; ++i)
    {
      scanf("%d", &a[i]);
      --a[i];
    }

    vector<int> ans = solve();

    for (int i = 0; i < m; ++i)
      printf("%d%c", ans[i] + 1, i + 1 < m ? ' ' : '\n');
  }
  return 0;
}
