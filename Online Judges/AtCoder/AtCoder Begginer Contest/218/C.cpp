#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 200; int n;
char s[maxN][maxN + 1], t[maxN][maxN + 1], aux[maxN][maxN + 1];
set<pair<int, int>> ss, tt;

set<pair<int, int>> normalize(set<pair<int, int>> &a)
{
  set<pair<int, int>> aa;
  int i = a.begin()->first, j = a.begin()->second;
  for (auto &p: a) aa.insert({p.first - i, p.second - j});
  return(aa);
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      scanf(" %s", s[i]);
    for (int i = 0; i < n; i++)
      scanf(" %s", t[i]);

    ss.clear();
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (s[i][j] == '#')
          ss.insert(make_pair(i, j));
    ss = normalize(ss);

    bool can = false;

    tt.clear();
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (t[i][j] == '#')
          tt.insert(make_pair(i, j));
    tt = normalize(tt);
    can |= ss == tt;

    tt.clear();
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (t[j][n - i - 1] == '#')
          tt.insert(make_pair(i, j));
    tt = normalize(tt);
    can |= ss == tt;

    tt.clear();
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (t[n - i - 1][n - j - 1] == '#')
          tt.insert(make_pair(i, j));
    tt = normalize(tt);
    can |= ss == tt;

    tt.clear();
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (t[n - j - 1][i] == '#')
          tt.insert(make_pair(i, j));
    tt = normalize(tt);
    can |= ss == tt;

    printf("%s\n", can ? "Yes" : "No");
  }
  return 0;
}