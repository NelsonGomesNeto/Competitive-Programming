#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 10; int n;
struct Pos
{
  int x, y;
  void read() { scanf("%d %d", &x, &y); }
  bool operator==(const Pos &other) const { return x == other.x && y == other.y; }
};
Pos now[maxN], dest[maxN];
Pos aux1[maxN], aux2[maxN];

void printAll()
{
  printf("\tall:\n");
  for (int i = 0; i < n; i ++)
    printf("%d %d\n", now[i].x, now[i].y);
}

int main()
{
  scanf("%d", &n);
  vector<pair<char, Pos>> ans, ans1, ans2;

  for (int i = 0; i < n; i ++)
    now[i].read();
  for (int i = 0; i < n; i ++)
    dest[i].read();
  memcpy(aux1, now, sizeof(now)), memcpy(aux2, dest, sizeof(dest));

  {
    // fix columns
    sort(now, now+n, [](const Pos &a, const Pos &b) { return a.x < b.x; });
    sort(dest, dest+n, [](const Pos &a, const Pos &b) { return a.x < b.x; });
    while (1)
    {
      for (int i = 0; i < n; i ++)
      {
        while (now[i].x != dest[i].x)
        {
          int nextX = now[i].x + (dest[i].x - now[i].x > 0 ? 1 : -1);
          bool cant = false;
          for (int j = i + 1; j < n; j ++)
            if (nextX == now[j].x)
              cant = true;
          if (cant) break;
          ans1.push_back({dest[i].x - now[i].x > 0 ? 'R' : 'L', {now[i].x, now[i].y}});
          now[i].x += dest[i].x - now[i].x > 0 ? 1 : -1;
        }
      }
      bool all = true;
      for (int i = 0; i < n; i ++)
        if (now[i].x != dest[i].x)
          all = false;
      if (all) break;
    }
    DEBUG printAll();

    Pos auxNow[maxN], auxDest[maxN];
    memcpy(auxNow, now, sizeof(now));
    memcpy(auxDest, dest, sizeof(dest));
    vector<pair<char, Pos>> lo, hi;

    {
      sort(now, now+n, [](const Pos &a, const Pos &b) { return a.y < b.y; });
      sort(dest, dest+n, [](const Pos &a, const Pos &b) { return a.y < b.y; });
      int orig = now[0].y;
      for (int i = 0; i < n; i ++)
      {
        int dy = min(orig, dest[0].y) - (2*n - 2*(i - 1));
        while (now[i].y != dy)
        {
          lo.push_back({'D', {now[i].x, now[i].y}});
          now[i].y += (dy - now[i].y) > 0 ? 1 : -1;
        }
      }
      DEBUG printAll();

      sort(now, now+n, [](const Pos &a, const Pos &b) { return a.y > b.y; });
      sort(dest, dest+n, [](const Pos &a, const Pos &b) { return a.y > b.y; });
      for (int i = 0, ii; i < n; i ++)
      {
        for (ii = 0; ii < n && now[ii].x != dest[i].x; ii ++);
        DEBUG printf("now %d %d - dest %d %d\n", now[ii].y, now[ii].x, dest[i].x, dest[i].y);
        while (now[ii].y != dest[i].y)
        {
          int nextI = now[ii].y + (dest[i].y - now[ii].y > 0 ? 1 : -1);
          bool problem = false;
          for (int j = 0; j < n; j ++)
            if (now[j].y == nextI)
            {
              lo.push_back({'T', {now[j].x, now[j].y}});
              problem = true;
              break;
            }
          lo.push_back({'U', {now[ii].x, now[ii].y}});
          if (problem)
            lo.push_back({'U', {now[ii].x, now[ii].y + 1}});
          for (int j = 0; j < n; j ++)
            if (now[j].y == nextI)
            {
              lo.push_back({'P', {now[j].x, now[j].y}});
              break;
            }
          now[ii].y = nextI + (dest[i].y - now[ii].y > 0 ? 1 : -1)*problem;
        }
      }
      DEBUG printAll();
    }
    {
      memcpy(now, auxNow, sizeof(now));
      memcpy(dest, auxDest, sizeof(dest));
      sort(now, now+n, [](const Pos &a, const Pos &b) { return a.y > b.y; });
      sort(dest, dest+n, [](const Pos &a, const Pos &b) { return a.y > b.y; });
      int orig = now[0].y;
      for (int i = 0; i < n; i ++)
      {
        int dy = max(orig, dest[0].y) + (2*n - 2*(i - 1));
        while (now[i].y != dy)
        {
          hi.push_back({'U', {now[i].x, now[i].y}});
          now[i].y += (dy - now[i].y) > 0 ? 1 : -1;
        }
      }
      DEBUG printAll();

      sort(now, now+n, [](const Pos &a, const Pos &b) { return a.y < b.y; });
      sort(dest, dest+n, [](const Pos &a, const Pos &b) { return a.y < b.y; });
      for (int i = 0, ii; i < n; i ++)
      {
        for (ii = 0; ii < n && now[ii].x != dest[i].x; ii ++);
        DEBUG printf("now %d %d - dest %d %d\n", now[ii].y, now[ii].x, dest[i].x, dest[i].y);
        while (now[ii].y != dest[i].y)
        {
          int nextI = now[ii].y + (dest[i].y - now[ii].y > 0 ? 1 : -1);
          bool problem = false;
          for (int j = 0; j < n; j ++)
            if (now[j].y == nextI)
            {
              hi.push_back({'T', {now[j].x, now[j].y}});
              problem = true;
              break;
            }
          hi.push_back({'D', {now[ii].x, now[ii].y}});
          if (problem)
            hi.push_back({'D', {now[ii].x, now[ii].y - 1}});
          for (int j = 0; j < n; j ++)
            if (now[j].y == nextI)
            {
              hi.push_back({'P', {now[j].x, now[j].y}});
              break;
            }
          now[ii].y = nextI + (dest[i].y - now[ii].y > 0 ? 1 : -1)*problem;
        }
      }
      DEBUG printAll();
    }

    bool valid = true;
    for (int i = 0; i < n; i ++)
    {
      bool found = false;
      for (int j = 0; j < n; j ++)
        if (now[i] == dest[j])
          found = true;
      if (!found) valid = false;
    }
    DEBUG printf("%d\n", valid);

    if (lo.size() < hi.size())
      for (auto p: lo) ans1.push_back(p);
    else
      for (auto p: hi) ans1.push_back(p);
    lo.clear(), hi.clear();
  }

  {
    memcpy(now, aux1, sizeof(now)), memcpy(dest, aux2, sizeof(dest));
    for (int i = 0; i < n; i ++) swap(now[i].x, now[i].y);
    for (int i = 0; i < n; i ++) swap(dest[i].x, dest[i].y);

    // fix columns
    sort(now, now+n, [](const Pos &a, const Pos &b) { return a.x < b.x; });
    sort(dest, dest+n, [](const Pos &a, const Pos &b) { return a.x < b.x; });
    while (1)
    {
      for (int i = 0; i < n; i ++)
      {
        while (now[i].x != dest[i].x)
        {
          int nextX = now[i].x + (dest[i].x - now[i].x > 0 ? 1 : -1);
          bool cant = false;
          for (int j = i + 1; j < n; j ++)
            if (nextX == now[j].x)
              cant = true;
          if (cant) break;
          ans2.push_back({dest[i].x - now[i].x > 0 ? 'R' : 'L', {now[i].x, now[i].y}});
          now[i].x += dest[i].x - now[i].x > 0 ? 1 : -1;
        }
      }
      bool all = true;
      for (int i = 0; i < n; i ++)
        if (now[i].x != dest[i].x)
          all = false;
      if (all) break;
    }
    DEBUG printAll();

    Pos auxNow[maxN], auxDest[maxN];
    memcpy(auxNow, now, sizeof(now));
    memcpy(auxDest, dest, sizeof(dest));
    vector<pair<char, Pos>> lo, hi;

    {
      sort(now, now+n, [](const Pos &a, const Pos &b) { return a.y < b.y; });
      sort(dest, dest+n, [](const Pos &a, const Pos &b) { return a.y < b.y; });
      int orig = now[0].y;
      for (int i = 0; i < n; i ++)
      {
        int dy = min(orig, dest[0].y) - (2*n - 2*(i - 1));
        while (now[i].y != dy)
        {
          lo.push_back({'D', {now[i].x, now[i].y}});
          now[i].y += (dy - now[i].y) > 0 ? 1 : -1;
        }
      }
      DEBUG printAll();

      sort(now, now+n, [](const Pos &a, const Pos &b) { return a.y > b.y; });
      sort(dest, dest+n, [](const Pos &a, const Pos &b) { return a.y > b.y; });
      for (int i = 0, ii; i < n; i ++)
      {
        for (ii = 0; ii < n && now[ii].x != dest[i].x; ii ++);
        DEBUG printf("now %d %d - dest %d %d\n", now[ii].y, now[ii].x, dest[i].x, dest[i].y);
        while (now[ii].y != dest[i].y)
        {
          int nextI = now[ii].y + (dest[i].y - now[ii].y > 0 ? 1 : -1);
          bool problem = false;
          for (int j = 0; j < n; j ++)
            if (now[j].y == nextI)
            {
              lo.push_back({'T', {now[j].x, now[j].y}});
              problem = true;
              break;
            }
          lo.push_back({'U', {now[ii].x, now[ii].y}});
          if (problem)
            lo.push_back({'U', {now[ii].x, now[ii].y + 1}});
          for (int j = 0; j < n; j ++)
            if (now[j].y == nextI)
            {
              lo.push_back({'P', {now[j].x, now[j].y}});
              break;
            }
          now[ii].y = nextI + (dest[i].y - now[ii].y > 0 ? 1 : -1)*problem;
        }
      }
      DEBUG printAll();
    }
    {
      memcpy(now, auxNow, sizeof(now));
      memcpy(dest, auxDest, sizeof(dest));
      sort(now, now+n, [](const Pos &a, const Pos &b) { return a.y > b.y; });
      sort(dest, dest+n, [](const Pos &a, const Pos &b) { return a.y > b.y; });
      int orig = now[0].y;
      for (int i = 0; i < n; i ++)
      {
        int dy = max(orig, dest[0].y) + (2*n - 2*(i - 1));
        while (now[i].y != dy)
        {
          hi.push_back({'U', {now[i].x, now[i].y}});
          now[i].y += (dy - now[i].y) > 0 ? 1 : -1;
        }
      }
      DEBUG printAll();

      sort(now, now+n, [](const Pos &a, const Pos &b) { return a.y < b.y; });
      sort(dest, dest+n, [](const Pos &a, const Pos &b) { return a.y < b.y; });
      for (int i = 0, ii; i < n; i ++)
      {
        for (ii = 0; ii < n && now[ii].x != dest[i].x; ii ++);
        DEBUG printf("now %d %d - dest %d %d\n", now[ii].y, now[ii].x, dest[i].x, dest[i].y);
        while (now[ii].y != dest[i].y)
        {
          int nextI = now[ii].y + (dest[i].y - now[ii].y > 0 ? 1 : -1);
          bool problem = false;
          for (int j = 0; j < n; j ++)
            if (now[j].y == nextI)
            {
              hi.push_back({'T', {now[j].x, now[j].y}});
              problem = true;
              break;
            }
          hi.push_back({'D', {now[ii].x, now[ii].y}});
          if (problem)
            hi.push_back({'D', {now[ii].x, now[ii].y - 1}});
          for (int j = 0; j < n; j ++)
            if (now[j].y == nextI)
            {
              hi.push_back({'P', {now[j].x, now[j].y}});
              break;
            }
          now[ii].y = nextI + (dest[i].y - now[ii].y > 0 ? 1 : -1)*problem;
        }
      }
      DEBUG printAll();
    }

    bool valid = true;
    for (int i = 0; i < n; i ++)
    {
      bool found = false;
      for (int j = 0; j < n; j ++)
        if (now[i] == dest[j])
          found = true;
      if (!found) valid = false;
    }
    DEBUG printf("%d\n", valid);

    if (lo.size() < hi.size())
      for (auto p: lo) ans2.push_back(p);
    else
      for (auto p: hi) ans2.push_back(p);
  }

  // if (ans.size() > 2050)
  //   while (1);
  if (ans1.size() < ans2.size())
    ans = ans1;
  else
  {
    for (int i = 0; i < ans2.size(); i ++)
    {
      swap(ans2[i].second.x, ans2[i].second.y);
      if (ans2[i].first == 'D')
        ans2[i].first = 'U';
      else if (ans2[i].first == 'U')
        ans2[i].first = 'D';
      else if (ans2[i].first == 'L')
        ans2[i].first = 'R';
      else if (ans2[i].first == 'R')
        ans2[i].first = 'L';
    }
    ans = ans2;
  }

  printf("%d\n", (int) ans.size());
  for (int i = 0; i < ans.size(); i ++)
    printf("%d %d %c\n", ans[i].second.x, ans[i].second.y, ans[i].first);

  return 0;
}