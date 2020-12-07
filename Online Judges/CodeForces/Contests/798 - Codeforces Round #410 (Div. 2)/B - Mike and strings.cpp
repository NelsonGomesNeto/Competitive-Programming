#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

int equal(string a, string b, int shift)
{
  for (int all = 0, i = shift; all < a.size(); all ++, i ++)
  {
    i %= a.size();
    if (a[all] != b[i]) return(0);
  }
  return(1);
}

int main()
{
  int n; scanf("%d", &n);
  string s[n]; cin >> s[0];
  set<string> allStrings;
  for (int i = 0; i < s[0].size(); i ++)
  {
    allStrings.insert(s[0]);
    rotate(s[0].begin(), s[0].begin()+1, s[0].end());
  }

  int can = 1;
  for (int i = 1; i < n; i ++)
  {
    cin >> s[i];
    if (!allStrings.count(s[i])) can = 0;
  }

  if (!can) printf("-1\n");
  else
  {
    int start[n]; start[0] = 0;
    for (int i = 1; i < n; i ++)
    {
      int j = 0;
      while (!equal(s[0], s[i], j)) j ++;
      start[i] = j;
    }
    DEBUG for (int i = 0; i < n; i ++) printf("%d%c", start[i], i < n - 1 ? ' ' : '\n');
    DEBUG printf("%d\n", (int) allStrings.size());

    int minCost = 999999;
    for (int i = 0; i < allStrings.size(); i ++)
    {
      int now = 0;
      for (int j = 0; j < n; j ++)
      {
        if (start[j] < i) now += (allStrings.size() - i) + start[j];
        else now += start[j] - i;
      }
      minCost = min(minCost, now);
    }
    printf("%d\n", minCost);
  }

  return(0);
}
