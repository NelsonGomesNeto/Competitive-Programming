#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e3; int n;
lli a[maxN][5];
map<vector<int>, int> cnt;

vector<int> merge(vector<int> &a1, vector<int> a2)
{
  vector<int> ans(5);
  for (int i = 0; i < 5; i++) ans[i] = max(a1[i], a2[i]);
  return ans;
}
bool bruteForce(map<vector<int>, int>::iterator it = cnt.begin(), int chosen = 0, vector<int> curr = {0, 0, 0, 0, 0})
{
  if (chosen == 3 && *min_element(curr.begin(), curr.end()) == 1)
    return true;
  if (it == cnt.end())
    return false;

  if (bruteForce(next(it), chosen, curr))
    return true;
  for (int j = 1; chosen + j <= 3 && j <= it->second; j++)
  {
    curr = merge(curr, it->first);
    if (bruteForce(next(it), chosen + j, curr))
      return true;
  }
  return false;
}

bool can(lli x)
{
  cnt.clear();
  for (int i = 0; i < n; i++)
  {
    vector<int> b(5);
    for (int j = 0; j < 5; j++)
      b[j] = a[i][j] >= x;
    if (!cnt.count(b)) cnt[b] = 0;
    cnt[b]++;
  }

  return bruteForce();
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      for (int j = 0; j < 5; j++)
        scanf("%lld", &a[i][j]);

    lli lo = 0, hi = 1e9;
    while (lo < hi)
    {
      lli mid = (lo + hi + 1) >> 1LL;
      if (can(mid)) lo = mid;
      else hi = mid - 1;
    }

    printf("%lld\n", lo);
  }
  return 0;
}