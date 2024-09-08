#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

bool better(pair<int, int> a, pair<int, int> b, bool alice)
{
  if (alice)
  {
    if (a.first > b.first || (a.first == b.first && a.second < b.second))
      return true;
    return false;
  }
  else
  {
    if (a.second > b.second || (a.second == b.second && a.first < b.first))
      return true;
    return false;
  }
}

pair<int, int> solve(int x, int y, bool serving = true, bool alice = true)
{
  pair<int, int> ans = {0, 0};
  if (x == 0 && y == 0)
  {
    if (!serving)
    {
      if (alice) ans.second += 1;
      else ans.first += 1;
    }
    return ans;
  }

  if (alice)
  {
    if (serving)
    {
      if (x) ans = solve(x - 1, y, false, !alice);
      else ans = solve(x, y, true, !alice);
    }
    else
    {
      pair<int, int> hit = {-1, -1}, notHit = {0, 0};
      if (x) hit = solve(x - 1, y, false, !alice);
      notHit = solve(x, y, true, !alice);
      notHit.second += 1;

      if (better(hit, notHit, alice)) ans = hit;
      else ans = notHit;
    }
  }
  else
  {
    if (serving)
    {
      if (y) ans = solve(x, y - 1, false, !alice);
      else ans = solve(x, y, true, !alice);
    }
    else
    {
      pair<int, int> hit = {-1, -1}, notHit = {0, 0};
      if (y) hit = solve(x, y - 1, false, !alice);
      notHit = solve(x, y, true, !alice);
      notHit.first += 1;

      if (better(hit, notHit, alice)) ans = hit;
      else ans = notHit;
    }
  }
  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int x, y; scanf("%d %d", &x, &y);
    int alice, bob;
    if (y > x)
      bob = y, alice = max(0, x - 1);
    else if (y == x)
      bob = y, alice = max(0, x - 1);
    else
      alice = max(0, x - 1), bob = y;
    DEBUG {
      pair<int, int> ans = solve(x, y);
      printf("\t%d %d\n", ans.first, ans.second);
    }
    printf("%d %d\n", alice, bob);
  }
  return 0;
}
