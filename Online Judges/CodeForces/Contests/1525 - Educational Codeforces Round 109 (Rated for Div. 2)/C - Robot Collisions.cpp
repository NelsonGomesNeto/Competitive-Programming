#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n, m;
int a[maxN];
char d[maxN + 1];
int ans[maxN];

struct Robot
{
  int pos; char dir; int idx; bool mod;
  bool operator<(const Robot &other) const
  {
    return pos < other.pos;
  }
  int distance1(const Robot &other)
  {
    return abs(pos - other.pos) / 2;
  }
  int distance2(const Robot &other)
  {
    if (dir == 'R')
      return m - max(pos, other.pos) + abs(pos - other.pos) / 2;
    return min(pos, other.pos) + abs(pos - other.pos) / 2;
  }
  int distance3(const Robot &other)
  {
    assert(dir == 'L'), assert(other.dir == 'R');
    return pos + (m - other.pos) + abs(pos - other.pos) / 2;
  }
};
Robot robots[maxN];
stack<Robot> s[2];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    for (int i = 0; i < n; i++)
      scanf(" %c", &d[i]);

    for (int i = 0; i < n; i++)
      robots[i] = {a[i], d[i], i, (a[i] & 1) == 1};

    for (int i = 0; i < n; i++) ans[i] = -1;

    sort(robots, robots+n);

    for (int i = 0; i < 2; i++)
      while (!s[i].empty())
        s[i].pop();

    // opposite direction, no reflections
    for (int i = 0; i < n; i++)
    {
      if (robots[i].dir == 'L')
      {
        if (!s[robots[i].mod].empty() && s[robots[i].mod].top().dir == 'R')
        {
          ans[s[robots[i].mod].top().idx] = ans[robots[i].idx] = robots[i].distance1(s[robots[i].mod].top());
          s[robots[i].mod].pop();
        }
        else s[robots[i].mod].push(robots[i]);
      }
      else
        s[robots[i].mod].push(robots[i]);
    }

    // same direction, one reflect
    for (int k = 0; k < 2; k++)
    {
      // rights
      for (int i = n - 1; i >= 0; i--)
        if (ans[robots[i].idx] == -1 && robots[i].dir == 'R' && (robots[i].mod) == k)
        {
          int j = i - 1;
          while (j >= 0 && !(ans[robots[j].idx] == -1 && robots[j].dir == 'R' && (robots[i].mod) == (robots[j].mod)))
            j--;

          if (j >= 0)
            ans[robots[i].idx] = ans[robots[j].idx] = robots[i].distance2(robots[j]);
          i = j;
        }
      // lefts
      for (int i = 0; i < n; i++)
        if (ans[robots[i].idx] == -1 && robots[i].dir == 'L' && (robots[i].mod) == k)
        {
          int j = i + 1;
          while (j < n && !(ans[robots[j].idx] == -1 && robots[j].dir == 'L' && (robots[j].mod) == (robots[i].mod)))
            j++;

          if (j < n)
            ans[robots[i].idx] = ans[robots[j].idx] = robots[i].distance2(robots[j]);
          i = j;
        }
    }

    // opposite directions, two reflections (one for each side)
    for (int k = 0; k < 2; k++)
      for (int i = 0, j = n - 1; i < j; i++, j--)
      {
        while (i < j && !((robots[i].mod) == k && ans[robots[i].idx] == -1 && robots[i].dir == 'L')) i++;
        while (i < j && !((robots[j].mod) == k && ans[robots[j].idx] == -1 && robots[j].dir == 'R')) j--;

        if (i < j)
          ans[robots[i].idx] = ans[robots[j].idx] = robots[i].distance3(robots[j]);
      }

    for (int i = 0; i < n; i++)
      printf("%d%c", ans[i], i == n - 1 ? '\n' : ' ');
  }
  return 0;
}
