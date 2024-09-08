#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int n, k;

int eval(int start)
{
  int curr = 0;
  set<int> sums;
  for (int i = start; i < k; i++)
    if (!sums.count(k - i))
    {
      curr++;

      list<int> toAdd;
      if (k - i > i)
        toAdd.push_back(i);
      for (int s: sums)
        if (s + i < k && k - (s + i) > i)
          toAdd.push_back(s + i);
      for (int s: toAdd)
        sums.insert(s);
    }
  return curr;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &k);
    vector<int> ans;
    int lo = 1, hi = k - 1;
    while (abs(hi - lo) > 3)
    {
      int midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi + 2) / 3;
      int elo = eval(midlo), ehi = eval(midhi);
      if (ehi == elo) lo = midlo, hi = midhi;
      else if (ehi > elo) lo = midlo;
      else hi = midhi;
    }
    int bestI = lo, bestEval = eval(lo);
    for (int i = lo + 1; i <= hi; i++)
    {
      int now = eval(i);
      if (now > bestEval)
        bestEval = now, bestI = i;
    }

    set<int> sums;
    for (int i = bestI; i < k; i++)
      if (!sums.count(k - i))
      {
        ans.push_back(i);

        list<int> toAdd;
        toAdd.push_back(i);
        for (int s: sums)
          if (s + i < k && k - (s + i) > i)
            toAdd.push_back(s + i);
        for (int s: toAdd)
          sums.insert(s);
      }

    for (int i = k + 1; i <= n; i++)
      ans.push_back(i);

    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); i++)
      printf("%d%c", ans[i], i < ans.size() - 1 ? ' ' : '\n');
  }
  return 0;
}