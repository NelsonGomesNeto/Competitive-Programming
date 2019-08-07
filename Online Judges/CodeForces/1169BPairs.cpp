#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 3e5, maxM = 3e5; int n, m;
int cnt[maxN];
map<int, int> cntOther[maxN];
pair<int, int> pairs[maxM];

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i ++)
  {
    scanf("%d %d", &pairs[i].first, &pairs[i].second);
    pairs[i].first --, pairs[i].second --;
    cnt[pairs[i].first] ++, cnt[pairs[i].second] ++;
    if (!cntOther[pairs[i].first].count(pairs[i].second))
      cntOther[pairs[i].first][pairs[i].second] = 0;
    cntOther[pairs[i].first][pairs[i].second] ++;
    if (!cntOther[pairs[i].second].count(pairs[i].first))
      cntOther[pairs[i].second][pairs[i].first] = 0;
    cntOther[pairs[i].second][pairs[i].first] ++;
  }
  vector<pair<int, int>> all;
  for (int i = 0; i < n; i ++)
    if (cnt[i])
      all.push_back({cnt[i], i});
  sort(all.begin(), all.end()); reverse(all.begin(), all.end());

  bool can = false;
  for (int i = 0; i < all.size() && !can; i ++)
    for (int j = i + 1; j < all.size() && all[i].first + all[j].first >= m && !can; j ++)
      can = all[i].first + all[j].first - cntOther[all[i].second][all[j].second] >= m;
  printf("%s\n", can ? "YES" : "NO");

  return(0);
}
