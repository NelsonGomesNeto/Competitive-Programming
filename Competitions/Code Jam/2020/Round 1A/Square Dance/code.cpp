#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int r, c;
vector<vector<int>> mat;
struct Pos
{
  int i, j;
  bool operator<(const Pos &other) const { return i < other.i || (i == other.i && j < other.j); }
};
set<Pos> guys;
vector<set<int>> rows[2], columns[2];
int di[4] = {0, 0, 1, -1}, dj[4] = {1, -1, 0, 0};

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    rows[0].clear(), columns[0].clear();
    rows[1].clear(), columns[1].clear();
    guys.clear(), mat.clear();
    scanf("%d %d", &r, &c);
    mat.resize(r, vector<int>(c));
    rows[0].resize(r), columns[0].resize(c);
    rows[1].resize(r), columns[1].resize(c);
    lli skill = 0;
    for (int i = 0; i < r; i++)
    {
      for (int j = 0; j < c; j++)
      {
        scanf("%d", &mat[i][j]);
        DEBUG printf("%d%c", mat[i][j], j < c - 1 ? ' ' : '\n');
        skill += mat[i][j];
        guys.insert({i, j});
        rows[0][i].insert(j);
        rows[1][i].insert(-j);
        columns[0][j].insert(i);
        columns[1][j].insert(-i);
      }
    }

    lli ans = 0;
    bool hadUpdate = false;
    do
    {
      set<Pos> updated, killed;
      ans += skill;
      for (Pos p: guys)
      {
        auto it = rows[0][p.i].lower_bound(p.j + 1);
        int right = -1;
        if (it != rows[0][p.i].end())
          right = *it;

        it = rows[1][p.i].lower_bound(-(p.j - 1));
        int left = -1;
        if (it != rows[1][p.i].end())
          left = -(*it);

        it = columns[0][p.j].lower_bound(p.i + 1);
        int down = -1;
        if (it != columns[0][p.j].end())
          down = *it;

        it = columns[1][p.j].lower_bound(-(p.i - 1));
        int up = -1;
        if (it != columns[1][p.j].end())
          up = -(*it);

        int d = (left >= 0 && mat[p.i][left] > 0) + (right >= 0 && mat[p.i][right] > 0) + (down >= 0 && mat[down][p.j] > 0) + (up >= 0 && mat[up][p.j] > 0);
        if (d != 0)
        {
          int total = (left >= 0 ? mat[p.i][left] : 0) + (right >= 0 ? mat[p.i][right] : 0) + (down >= 0 ? mat[down][p.j] : 0) + (up >= 0 ? mat[up][p.j] : 0);
          int totalValue = total / d + (total % d != 0);
          if (mat[p.i][p.j] < totalValue)
          {
            DEBUG printf("\t%d %d - %d %d - %d %d %d %d\n", p.i, p.j, mat[p.i][p.j], totalValue, left, right, down, up);
            skill -= mat[p.i][p.j];
            killed.insert(p);
            if (left >= 0 && mat[p.i][left] != 0) updated.insert({p.i, left});
            if (right >= 0 && mat[p.i][right] != 0) updated.insert({p.i, right});
            if (down >= 0 && mat[down][p.j] != 0) updated.insert({down, p.j});
            if (up >= 0 && mat[up][p.j] != 0) updated.insert({up, p.j});
          }
        }
      }

      for (Pos p: killed)
      {
        rows[0][p.i].erase(p.j);
        rows[1][p.i].erase(-p.j);
        columns[0][p.j].erase(p.i);
        columns[1][p.j].erase(-p.i);
        mat[p.i][p.j] = 0;
        updated.erase(p);
      }

      guys = updated;
      hadUpdate = !updated.empty();
    } while (hadUpdate);

    printf("Case #%d: %lld\n", tt, ans);
  }
  return 0;
}