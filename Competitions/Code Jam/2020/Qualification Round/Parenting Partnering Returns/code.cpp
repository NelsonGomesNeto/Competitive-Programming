#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3, maxT = 24*60 + 1; int n;
struct Activity
{
  int start, end, id;
  void read() { scanf("%d %d", &start, &end); }
  bool operator<(const Activity &other) const { return end < other.end || (end == other.end && start < other.start); }
};
Activity activities[maxN];
char ans[maxN + 1];

int memo[maxT][maxT], path[maxT][maxT];
int solve(int i = 0, int c = 0, int j = 0)
{
  if (i == n) return 0;
  if (memo[c][j] != -1) return memo[c][j];

  int cc = 0, jj = 0;
  if (activities[i].start >= c)
    cc = 1 + solve(i + 1, activities[i].end, j);
  if (activities[i].start >= j)
    jj = 1 + solve(i + 1, c, activities[i].end);
  path[c][j] = cc >= jj ? 0 : 1;
  return memo[c][j] = max(cc, jj);
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
      activities[i].read();
      activities[i].id = i;
    }
    sort(activities, activities+n);

    memset(memo, -1, sizeof(memo));
    int total = solve();
    if (total == n)
    {
      ans[n] = '\0';
      for (int i = 0, c = 0, j = 0; i < n; i++)
      {
        if (path[c][j] == 0)
          ans[activities[i].id] = 'C', c = activities[i].end;
        else
          ans[activities[i].id] = 'J', j = activities[i].end;
      }
    }
    printf("Case #%d: %s\n", tt, total == n ? ans : "IMPOSSIBLE");
  }
  return 0;
}