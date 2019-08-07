#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  pair<int, pair<int, int> > group[n];
  for (int i = 0; i < n; i ++)
  {
    scanf("%d %d", &group[i].second.first, &group[i].first);
    group[i].second.second = i;
  }
  sort(group, group+n);
  int m; scanf("%d", &m);
  pair<int, int> table[m];
  for (int i = 0; i < m; i ++)
  {
    scanf("%d", &table[i].first);
    table[i].second = i;
  }
  sort(table, table+m);

  int ans = 0, served = 0;
  vector<pair<int, int> > allocation;
  for (int i = n - 1; i >= 0; i --)
    for (int j = 0; j < m; j ++)
      if (table[j].first >= group[i].second.first)
      {
        table[j].first = 0;
        ans += group[i].first; served ++;
        allocation.push_back({group[i].second.second + 1, table[j].second + 1});
        break;
      }
  printf("%d %d\n", served, ans);
  for (int i = 0; i < served; i ++)
    printf("%d %d\n", allocation[i].first, allocation[i].second);

  return(0);
}