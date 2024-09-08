#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
vector<int> a;
vector<int> pos[maxN];

int calc(vector<int> &p)
{
  if (p.empty()) return n;

  int ans = 0, prv = -1;
  for (int i = 0; i < p.size(); i++)
  {
    if (prv + 1 < p[i])
      ans++;
    prv = p[i];
  }
  if (p.back() + 1 < n)
    ans++;
  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    a.resize(n);
    for (int i = 0; i < n; i++)
      pos[i].clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);  a[i]--;
      pos[a[i]].push_back(i);
    }

    int ans = n;
    for (int i = 0; i < n; i++)
      ans = min(ans, calc(pos[i]));
    printf("%d\n", ans);
  }
  return 0;
}
