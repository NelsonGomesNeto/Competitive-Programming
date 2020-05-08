#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int di[4] = {0, 1, 0, -1}, dj[4] = {1, 0, -1, 0};
int r, c;
vector<vector<int>> mat;
struct Pos
{
  int i, j;
  bool operator<(const Pos &other) const { return i < other.i || (i == other.i && j < other.j); }
};
vector<vector<Pos>> compasses[4];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    mat.clear();
    for (int i = 0; i < 4; i++) compasses[i].clear();

    scanf("%d %d", &r, &c);
    mat.resize(r, vector<int>(c));
    for (int i = 0; i < 4; i++) compasses[i].resize(r, vector<Pos>(c));

    set<Pos> competidors;
    lli totalSkill = 0;
    for (int i = 0; i < r; i++)
      for (int j = 0; j < c; j++)
      {
        scanf("%d", &mat[i][j]);
        competidors.insert({i, j});
        totalSkill += mat[i][j];
      }

    for (int i = 0; i < r; i++)
      for (int j = 0; j < c; j++)
        for (int k = 0; k < 4; k++)
        {
          int ni = i + di[k], nj = j + dj[k];
          if (ni >= 0 && ni < r && nj >= 0 && nj < c)
            compasses[k][i][j] = {ni, nj};
          else
            compasses[k][i][j] = {-1, -1};
        }

    lli ans = 0; bool hadUpdate = false;
    do
    {
      set<Pos> updated, toRemove;
      ans += totalSkill;

      for (Pos p: competidors)
      {
        int aliveCompasses = 0; lli compassesesSkillMean = 0;
        for (int k = 0; k < 4; k++)
        {
          Pos o = compasses[k][p.i][p.j];
          if (o.i != -1)
            aliveCompasses++, compassesesSkillMean += mat[o.i][o.j];
        }
        if (aliveCompasses)
        {
          compassesesSkillMean = compassesesSkillMean / aliveCompasses + (compassesesSkillMean % aliveCompasses != 0);
          if (compassesesSkillMean > mat[p.i][p.j])
            toRemove.insert(p);
        }
      }

      for (Pos p: toRemove)
      {
        for (int k = 0; k < 4; k++)
        {
          Pos o = compasses[k][p.i][p.j];
          if (o.i != -1)
          {
            compasses[(k + 2) % 4][o.i][o.j] = compasses[(k + 2) % 4][p.i][p.j];
            updated.insert(o);
          }
        }
        totalSkill -= mat[p.i][p.j];
      }
      for (Pos p: toRemove)
        updated.erase(p);

      competidors = updated;
      hadUpdate = !updated.empty();
    } while (hadUpdate);

    printf("Case #%d: %lld\n", tt, ans);
  }
  return 0;
}