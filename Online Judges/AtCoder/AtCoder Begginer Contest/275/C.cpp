#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 9; int n = 9;
char s[maxN][maxN + 1];

bool hasPawn(int i, int j)
{
  if (i < 0 || j < 0 || i >= n || j >= n) return false;
  return s[i][j] == '#';
}

struct Point
{
  int i, j;
  bool has() const { return hasPawn(i, j); }
  string toString() { return to_string(i + 1) + " " + to_string(j + 1); }
  bool operator<(const Point& other) const { return i < other.i || (i == other.i && j < other.j); }
};

int main()
{
  while (~scanf(" %s", s[0]))
  {
    for (int i = 1; i < n; ++i)
      scanf(" %s", s[i]);

    set<set<Point>> ans;
    for (int di = 0; di < n; ++di)
      for (int dj = 0; dj < n; ++dj)
      {
        if (di + dj < 1) continue;
        for (int i = 0; i < n; ++i)
          for (int j = 0; j < n; ++j)
          {
            bool valid = true;
            // di = 1, dj = 0
            auto now = set<Point>{{i, j}, {i - di, j + dj}, {i + dj, j + di}, {i - di + dj, j + dj + di}};
            for (const Point& p : now)
              valid &= p.has();
            // DEBUG
            //   if (valid)
            //     printf("\t%d | %s - %s - %s - %s\n", valid, now[0].toString().c_str(), now[1].toString().c_str(), now[2].toString().c_str(), now[3].toString().c_str());
            if (valid)
              ans.insert(now);
          }
      }

    printf("%d\n", ans.size());
  }
  return 0;
}
