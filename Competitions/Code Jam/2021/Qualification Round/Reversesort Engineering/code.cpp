#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n, c;
int ans[maxN];

int memo[maxN][maxN*maxN], path[maxN][maxN*maxN];
int turned[maxN], shouldBe[maxN];
int solve(int i = 0, int sum = 0)
{
  if (sum > c)
    return false;
  if (i == n - 1)
    return sum == c;
  int &ans = memo[i][sum];
  if (ans != -1)
    return ans;

  ans = 0;
  for (int toAdd = 1, maxToAdd = n - i; toAdd <= maxToAdd; toAdd++)
    if (solve(i + 1, sum + toAdd))
    {
      ans = 1;
      path[i][sum] = toAdd;
      break;
    }
  return ans;
}

int aux[maxN];
int eval()
{
  memcpy(aux, ans, sizeof(ans));
  int total = 0;
  for (int i = 0; i + 1 < n; i++)
  {
    int idx;
    for (int j = i; j < n; j++)
      if (aux[j] == i + 1)
      {
        idx = j;
        break;
      }
    reverse(aux+i, aux+idx+1);
    total += idx - i + 1;
  }
  return total;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &c);
    memset(memo, -1, sizeof(memo)), memset(path, 0, sizeof(path));
    bool can = solve();

    if (can)
    {
      memset(ans, 0, sizeof(ans));
      for (int i = 0, sum = 0, turn = 0; i + 1 < n; i++)
      {
        int toAdd = path[i][sum];
        int j = i + toAdd - 1;
        shouldBe[i] = j;
        sum += toAdd;
      }

      ans[n - 1] = n;
      for (int i = n - 2; i >= 0; i--)
      {
        ans[i] = i + 1;
        int j = shouldBe[i];
        reverse(ans+i, ans+j+1);
        DEBUG printf("\t%d %d\n", i + 1, j);
      }

      DEBUG printf("\t%d | %d\n", c, eval());
      // assert(eval() == c);

      printf("Case #%d: ", tt);
      for (int i = 0; i < n; i++)
        printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
    }
    else
      printf("Case #%d: IMPOSSIBLE\n", tt);
  }
  return 0;
}