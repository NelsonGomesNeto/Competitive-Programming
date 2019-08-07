#include <bits/stdc++.h>
using namespace std;
pair<pair<int, int>, set<int> > successors[(int) 1e3];

int main()
{
  int n; scanf("%d", &n);

  for (int i = 0; i < n; i ++)
  {
    int a, s; scanf("%d", &a);
    while (a --)
    {
      scanf("%d", &s);
      successors[i].second.insert(s - 1);
    }
    successors[i].first = {a, i};
  }
  sort(successors, successors+n);

  if (successors[0].first.second) printf("NO\n");
  else
  {
    vector<int> tree[n]; set<int> leafs; int done = 0;
    while (done < n)
    {
      int l = successors[done].first.first
      if (!canBeLeaf(l, leafs))
      leafs.insert(l);
      for (int i = 0; i < n; i ++)
      {
        successors[i].second.erase(l);
        successors[i].first.first = successors[i].second.size();
      }
      done ++;
    }
  }

  return(0);
}