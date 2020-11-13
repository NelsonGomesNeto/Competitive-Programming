#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
vector<lli> xs, ys;
map<lli, int> xcomp, ycomp;
void makeUnique(vector<lli> &a)
{
  sort(a.begin(), a.end());
  a.resize(distance(a.begin(), unique(a.begin(), a.end())));
}

struct Point
{
  lli x, y;
  void read() { scanf("%lld %lld", &x, &y); xs.push_back(x), ys.push_back(y); }
};
struct Segment
{
  Point a, b;
  void read() { a.read(); b.read(); }
};
Segment segments[maxN];

struct Block
{
  Point lu, rd; bool visited, outside, can[4];
  lli area()
  {
    return (abs(rd.x - lu.x) + 0) * (abs(lu.y - rd.y) + 0);
  }
  void print()
  {
    printf("(%lld, %lld) | (%lld, %lld) || %d %d %d %d\n", lu.x, lu.y, rd.x, rd.y, can[0], can[1], can[2], can[3]);
  }
};
vector<vector<Block>> mat;

set<lli> xwalls[maxN], ywalls[maxN];

int di[4] = {0, 0, 1, -1}, dj[4] = {1, -1, 0, 0};
lli getArea(int i, int j)
{
  if (mat[i][j].outside) return -1;
  if (mat[i][j].visited) return 0;
  mat[i][j].visited = true;

  printf("%d (%lld) %d (%lld) - %lld\n", j, xs[j], i, ys[i], mat[i][j].area());
  lli total = mat[i][j].area();
  for (int k = 0; k < 4; k++)
  {
    int ni = i + di[k], nj = j + dj[k];
    if (ni < 0 || nj < 0 || ni >= mat.size() || nj >= mat[0].size())
    {
      mat[i][j].outside = true;
      return -1;
    }
    if (!mat[i][j].can[k]) continue;

    lli res = getArea(ni, nj);
    if (res == -1)
    {
      mat[i][j].outside = true;
      return -1;
    }
    total += res;
  }
  return total;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    xs.clear(), ys.clear();
    for (int i = 0; i < n; i++)
      segments[i].read();

    makeUnique(xs), makeUnique(ys);
    xcomp.clear(), ycomp.clear();
    for (int i = 0; i < xs.size(); i++)
      xcomp[xs[i]] = i;
    for (int i = 0; i < ys.size(); i++)
      ycomp[ys[i]] = i;

    for (int i = 0; i < n; i++)
    {
      if (segments[i].a.x == segments[i].b.x) // vertical wall
      {
        for (int j = min(ycomp[segments[i].a.y], ycomp[segments[i].b.y]); j <= max(ycomp[segments[i].a.y], ycomp[segments[i].b.y]); j++)
        {
          printf("vertical wall on x = %lld | %lld to %lld\n", segments[i].a.x, segments[i].a.y, segments[i].b.y);
          xwalls[xcomp[segments[i].a.x]].insert(j);
        }
      }
      else // horizontal wall
      {
        for (int j = min(xcomp[segments[i].a.x], xcomp[segments[i].b.x]); j <= max(xcomp[segments[i].a.x], xcomp[segments[i].b.x]); j++)
        {
          ywalls[ycomp[segments[i].a.y]].insert(j);
        }
      }
    }

    mat.resize(ys.size() - 1, vector<Block>(xs.size() - 1));
    for (int i = 0; i < ys.size() - 1; i++)
      for (int j = 0; j < xs.size() - 1; j++)
      {
        mat[i][j] = Block{Point{xs[j], ys[i]}, Point{xs[j + 1], ys[i + 1]}, false, false};
        for (int k = 0; k < 4; k++)
        {
          mat[i][j].can[k] = true;
          if (k < 2)
          {
            if (k == 1 && xwalls[xcomp[mat[i][j].lu.x]].count(ycomp[mat[i][j].lu.y])) mat[i][j].can[1] = false;
            if (k == 0 && xwalls[xcomp[mat[i][j].rd.x]].count(ycomp[mat[i][j].rd.y])) mat[i][j].can[0] = false;
          }
          else
          {
            if (k == 2 && ywalls[ycomp[mat[i][j].rd.y]].count(xcomp[mat[i][j].rd.x])) mat[i][j].can[2] = false;
            if (k == 3 && ywalls[ycomp[mat[i][j].lu.y]].count(xcomp[mat[i][j].lu.x])) mat[i][j].can[3] = false;
          }
        }
        printf("%d %d: ", i, j); mat[i][j].print();
      }

    lli ans = 0;
    for (int i = 0; i < ys.size() - 1; i++)
      for (int j = 0; j < xs.size() - 1; j++)
      {
        if (!mat[i][j].visited)
        {
          printf("----------\n");
          lli area = getArea(i, j);
          if (area < 0) area = 0, mat[i][j].outside = true;
          ans += area;
          printf("\t%lld\n", area);
        }
      }
    printf("%lld\n", ans);
  }
  return 0;
}