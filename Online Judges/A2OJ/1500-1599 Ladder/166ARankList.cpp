#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

int compare(const pair<int, int> a, const pair<int, int> b)
{
  return(a.first < b.first || a.first == b.first && a.second > b.second);
}

int main()
{
  int n, k; scanf("%d %d", &n, &k);
  pair<int, int> team[n];
  for (int i = 0; i < n; i ++) scanf("%d %d", &team[i].first, &team[i].second);
  sort(team, team+n, compare);
  DEBUG for (int i = n - 1; i >= 0; i --)
    printf("%d - %d %d\n", n - i, team[i].first, team[i].second);

  int ans = 1, i;
  for (i = n - 1; i > 0; i --)
  {
    DEBUG printf("\t%d %d\n", n - i, i);
    ans = 1;
    while (i > 0 && team[i].first == team[i - 1].first && team[i].second == team[i - 1].second) { i --; ans ++; }
    if (n - i >= k) break;
  }
  if (team[0].first != team[1].first && n == k) ans = 1;

  printf("%d\n", ans);

  return(0);
}