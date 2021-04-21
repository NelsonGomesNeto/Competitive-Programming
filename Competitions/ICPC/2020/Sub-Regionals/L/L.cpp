#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 40; int n, m, q;
char s[maxN][maxN + 1];
char ss[maxN + 1];
vector<multiset<char>> ts;

set<int> has[maxN][maxN];
int di[8] = {1, 1, 1, 0, 0, -1, -1, -1}, dj[8] = {1, 0, -1, 1, -1, 1, 0, -1};
void fill(int i, int j, int idx)
{
  for (int k = 0; k < 8; k++)
  {
    int end = (ts[idx].size() - 1);
    int fi = i + end*di[k], fj = j + end*dj[k];
    if (fi >= 0 && fj >= 0 && fi < n && fj < m)
    {
      multiset<char> cnt;
      for (int d = 0; d <= end; d++)
        cnt.insert(s[i + d*di[k]][j + d*dj[k]]);
      if (cnt == ts[idx])
        for (int d = 0; d <= end; d++)
          has[i + d*di[k]][j + d*dj[k]].insert(idx);
    }
  }
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i++)
    scanf(" %s", s[i]);

  scanf("%d", &q);
  for (int i = 0; i < q; i++)
  {
    scanf(" %s", ss);
    multiset<char> cnt;
    for (auto c: string(ss))
      cnt.insert(c);
    ts.push_back(cnt);
  }

  for (int idx = 0; idx < q; idx++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        fill(i, j, idx);

  int ans = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      ans += has[i][j].size() > 1;
  printf("%d\n", ans);

  return 0;
}