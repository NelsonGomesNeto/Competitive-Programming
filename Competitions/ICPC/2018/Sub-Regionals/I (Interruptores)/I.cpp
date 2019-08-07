#include <bits/stdc++.h>
using namespace std;
set<pair<vector<int>, int> > visited;

int someOn(vector<int> lamp)
{
  for (int i = 0; i < lamp.size(); i ++) if (lamp[i]) return(1);
  return(0);
}

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  vector<int> lamp; for (int i = 0; i < m; i ++) lamp.push_back(0);
  int l; scanf("%d", &l);
  for (int i = 0, j; i < l ; i ++)
  {
    scanf("%d", &j); lamp[j - 1] = 1;
  }

  vector<int> s[n]; int ki;
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &ki);
    for (int j = 0, k; j < ki; j ++)
    {
      scanf("%d", &k);
      s[i].push_back(k - 1);
    }
  }
  // for (int i = 0; i < lamp.size(); i ++) printf("%d", lamp[i]); printf("\n");

  int i = 0;
  while (someOn(lamp))
  {
    int pos = i % n;
    if (visited.count({lamp, pos})) { i = -1; break; }
    visited.insert({lamp, pos});
    for (int j = 0; j < s[pos].size(); j ++)
      lamp[s[pos][j]] = !lamp[s[pos][j]];
    // for (int i = 0; i < lamp.size(); i ++) printf("%d", lamp[i]); printf("\n");
    i ++;
  }
  printf("%d\n", i);

  return(0);
}