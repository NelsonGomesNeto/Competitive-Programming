#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 400; int n;
char s[maxN][maxN + 1];

int di[4] = {1, 1, 0, 0}, dj[4] = {0, 1, 0, 1};

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf(" %s", s[i]);

    vector<pair<int, int>> pos;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (s[i][j] == '*')
          pos.push_back({i, j});

    if (pos[0].first == pos[1].first)
    {
      int i = pos[0].first + 1;
      if (i == n)
        i = pos[0].first - 1;
      s[i][pos[0].second] = '*';
      s[i][pos[1].second] = '*';
    }
    else if (pos[0].second == pos[1].second)
    {
      int j = pos[0].second + 1;
      if (j == n)
        j = pos[0].second - 1;
      s[pos[0].first][j] = '*';
      s[pos[1].first][j] = '*';
    }
    else
    {
      int basei = min(pos[0].first, pos[1].first);
      int basej = min(pos[0].second, pos[1].second);
      int deltai = abs(pos[0].first - pos[1].first);
      int deltaj = abs(pos[0].second - pos[1].second);

      for (int k = 0; k < 4; k++)
        s[basei + deltai*di[k]][basej + deltaj*dj[k]] = '*';
    }

    for (int i = 0; i < n; i++)
      printf("%s\n", s[i]);
  }
  return 0;
}
