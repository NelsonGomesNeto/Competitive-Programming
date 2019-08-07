#include <bits/stdc++.h>
using namespace std;

void all(vector<int> gifts, int i, int needed, set<vector<int> >& ways, vector<int> now)
{
  if (i == gifts.size())
  {
    sort(now.begin(), now.end());
    if (now.size() == needed) ways.insert(now);
    return;
  }
  all(gifts, i + 1, needed, ways, now);
  now.push_back(gifts[i]);
  all(gifts, i + 1, needed, ways, now);
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int n, m, k, d; scanf("%d %d %d %d", &n, &m, &k, &d);
    vector<int> normal, special;
    for (int i = 0, p; i < n; i ++)
    {
      scanf("%d", &p);
      if (p >= d) special.push_back(p);
      else normal.push_back(p);
    }
    int mk = m - k;
    printf("%d %d\n", normal.size(), special.size());
    set<vector<int> > nways, sways;
    vector<int> nn, ss;
    all(normal, 0, mk, nways, nn); all(special, 0, k, sways, ss);
    int ans = nways.size() * sways.size();
    printf("%d\n", ans);
  }
  return(0);
}