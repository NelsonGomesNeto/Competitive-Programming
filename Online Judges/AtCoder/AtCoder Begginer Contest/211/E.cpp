#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 8, maxK = 8; int n, k;
char ss[maxN * maxN + 1];
string s;

void printMat()
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      printf("%c", s[i*n + j]);
    printf("\n");
  }
}

int di[4] = {1, -1, 0, 0}, dj[4] = {0, 0, 1, -1};

set<set<pair<int, int>>> ways[maxK + 1];
set<pair<int, int>> normalize(set<pair<int, int>> way)
{
  set<pair<int, int>> nway;
  int i = way.begin()->first, j = way.begin()->second;
  for (auto &p: way) nway.insert(make_pair(p.first - i, p.second - j));
  return nway;
}

int main()
{
  while (~scanf("%d %d", &n, &k))
  {
    s = "";
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", ss);
      s += string(ss);
    }

    for (int sz = 0; sz <= k; sz++) ways[sz].clear();
    ways[1].insert(set<pair<int, int>> { make_pair(0, 0) });
    for (int sz = 1; sz < k; sz++)
    {
      for (auto &way: ways[sz])
        for (auto &p: way)
          for (int d = 0; d < 4; d++)
          {
            int ni = p.first + di[d], nj = p.second + dj[d];
            auto np = make_pair(ni, nj);
            if (!way.count(np))
            {
              set<pair<int, int>> nway = way;
              nway.insert(np);
              nway = normalize(nway);
              ways[sz + 1].insert(nway);
            }
          }
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        for (auto &way: ways[k])
        {
          bool valid = true;
          for (auto &p: way)
          {
            int ni = i + p.first, nj = j + p.second;
            int pp = ni * n + nj;
            if (!(ni >= 0 && nj >= 0 && ni < n && nj < n && s[pp] == '.'))
            {
              valid = false;
              break;
            }
          }
          ans += valid;
        }
    printf("%d\n", ans);
  }
  return 0;
}