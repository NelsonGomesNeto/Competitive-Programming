#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxS = 15, maxN = 1e4; int n;
char ss[maxS + 1];
string s;

char getLetter(int i, int j)
{
  int start = n - i - 1;
  int p = j - start;
  if (p < s.size())
    return s[p];
  return '#';
}
int di[2] = {0, 1}, dj[2] = {1, 0};
lli memo[maxS][maxS][maxN];
lli solve(int i, int j, int k = 0)
{
  // printf("\t%d %d %d\n", i, j, k);
  if (i >= n || j >= n - 1 + s.size()) return 0;
  if (getLetter(i, j) != s[k])
    return 0;
  if (k == s.size() - 1) return 1;

  int jj = j - (n - i - 1);
  lli &ans = memo[k][jj][i];
  if (ans != -1) return ans;

  ans = 0;
  for (int d = 0; d < 2; d++)
    ans += solve(i + di[d], j + dj[d], k + 1);
  
  return ans;
}

int main()
{
  while (~scanf("%d", &n))
  {
    scanf(" %s", ss);
    s = string(ss);

    memset(memo, -1, sizeof(memo));
    lli ans = 0;
    for (int i = 0; i < n; i++)
    {
      int start = n - i - 1;
      for (int j = 0; j < s.size(); j++)
        ans += solve(i, start + j);

      DEBUG {
        for (int j = 0; j < n - 1 + s.size(); j++)
          printf("%c", getLetter(i, j));
        printf("\n");
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}