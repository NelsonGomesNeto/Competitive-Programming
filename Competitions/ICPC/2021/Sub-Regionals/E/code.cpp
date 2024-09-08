#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e4, maxT = 2e5 + 11; int n;
struct Person
{
  int t, d;
  void read() { scanf("%d %d", &t, &d); }
  bool operator<(const Person &other) const { return t < other.t; }
};
Person ps[maxN];
int in[maxT + 1][2], out[maxT + 1][2];
int maxt[2] = {-100, -100};

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i <= maxT; i++) in[i][0] = in[i][1] = out[i][0] = out[i][1] = 0;

    for (int i = 0; i < n; i++)
    {
      ps[i].read();
      in[ps[i].t][ps[i].d]++;
    }
    sort(ps, ps+n);

    int ans = 0;
    bool otherHas = false;
    int dir = -1;
    for (int i = 0; i <= maxT; i++)
    {
      if (dir != -1 && maxt[dir] <= i)
      {
        if (otherHas)
        {
          ans = max(ans, maxt[dir] + 10);
          maxt[1 - dir] = maxt[dir] + 10;
          maxt[dir] = -100;
          dir = 1 - dir;
          otherHas = false;
        }
        else
        {
          ans = max(ans, maxt[dir]);
          dir = -1;
        }
      }

      for (int j = 0; j < 2; j++)
        if (in[i][j])
        {
          if (dir == j || dir == -1)
          {
            dir = j;
            maxt[dir] = i + 10;
            ans = max(ans, maxt[dir]);
          }
          else
          {
            otherHas = true;
          }
        }
    }
    if (dir != -1)
    {
      if (otherHas)
      {
        ans = max(ans, maxt[dir] + 10);
        maxt[1 - dir] = maxt[dir] + 10;
        maxt[dir] = -100;
        dir = 1 - dir;
        otherHas = false;
      }
      else
      {
        ans = max(ans, maxt[dir]);
        dir = -1;
      }
    }
    // printf("\t%d %d %d\n", dir, maxt[0], maxt[1]);

    printf("%d\n", ans);
  }
  return 0;
}