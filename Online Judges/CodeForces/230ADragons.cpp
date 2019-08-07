#include <bits/stdc++.h>
using namespace std;

int main()
{
  int s, n; scanf("%d %d", &s, &n);

  vector<pair<int, int> > dragon; int u, v;
  for (int i = 0; i < n; i ++)
  {
    scanf("%d %d", &u, &v);
    dragon.push_back({u, v});
  }

  sort(dragon.begin(), dragon.end());

  for (int i = 0; i < n; i ++)
  {
    if (dragon[i].first >= s)
    {
      printf("NO\n"); return(0);
    }
    else
      s += dragon[i].second;
  }
  printf("YES\n");

  return(0);
}