#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
char s[maxN + 1];
map<char, set<int>> pos;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    vector<pair<char, char>> all = {{'[', ']'}, {'(', ')'}};
    for (auto &[open, close]: all)
      pos[open].clear(), pos[close].clear();

    scanf(" %s", s);
    n = strlen(s);

    for (int i = 0; i < n; i++)
      pos[s[i]].insert(i);

    int ans = 0;
    for (auto &[open, close]: all)
      for (int lo: pos[open])
      {
        auto it = pos[close].upper_bound(lo);
        if (it != pos[close].end())
          ans++, pos[close].erase(it);
      }

    printf("%d\n", ans);
  }
  return 0;
}
