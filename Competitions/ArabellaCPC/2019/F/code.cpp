#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n, p;
int songs[maxN], chairs[maxN];
int chairMap[maxN][maxN];

int memo[maxN][maxN];
int path[maxN][maxN];
int solve(int i = 0, int pos = p)
{
  DEBUG printf("\t%d %d\n", i, pos);
  if (i == n - 1) return 1;
  int &ans = memo[i][pos];
  if (ans != -1) return ans;

  ans = 0;
  int sz = n - i, removedChair = chairMap[i][chairs[i]];
  int newPos = (pos + songs[i]) % sz;
  DEBUG printf("\t\t%d %d - %d\n", i, pos, newPos);

  int plus = 0;
  if (newPos != removedChair) plus = solve(i + 1, newPos - (newPos > removedChair));
  if (plus) path[i][pos] = 1;

  newPos = ((pos - songs[i]) % sz + sz) % sz;
  DEBUG printf("\t\t%d %d - %d\n", i, pos, newPos);
  int minus = 0;
  if (newPos != removedChair) minus = solve(i + 1, newPos - (newPos > removedChair));
  if (minus) path[i][pos] = 2;

  return ans = max(plus, minus);
}

int main()
{
  while (~scanf("%d %d", &n, &p))
  {
    p--;
    for (int i = 0; i < n - 1; i++) scanf("%d", &songs[i]);
    for (int i = 0; i < n - 1; i++)
    {
      scanf("%d", &chairs[i]);
      chairs[i]--;
    }

    list<int> curr;
    for (int i = 0; i < n; i++)
    {
      curr.push_back(i);
      chairMap[0][i] = i;
    }

    for (int i = 0; i + 1 < n; i++)
    {
      for (auto it = curr.begin(); it != curr.end(); it++)
        if (*it == chairs[i])
        {
          curr.erase(it);
          break;
        }
      assert(curr.size() == n - i - 1);
      int now = 0;
      for (auto it = curr.begin(); it != curr.end(); it++)
        chairMap[i + 1][*it] = now++;
    }

    memset(memo, -1, sizeof(memo));
    memset(path, -1, sizeof(path));
    int ans = solve();
    printf("%s\n", ans ? "Yes" : "No");

    DEBUG {
      for (int i = 0, pos = p; i < n - 1; i++)
      {
        printf("\t%s\n", path[i][pos] == 1 ? "+" : "-");
        int sz = n - i, removedChair = chairMap[i][chairs[i]];
        if (path[i][pos] == 1)
          pos = (pos + songs[i]) % sz;
        else
          pos = ((pos - songs[i]) % sz + sz) % sz;
        pos -= pos > removedChair;
      }
    }
  }
  return 0;
}