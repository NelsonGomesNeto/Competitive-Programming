#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e3;
char ss[maxN + 1];
string s, t;

int memo[maxN + 1][maxN + 1];
int path[maxN + 1][maxN + 1]; // 0 - left, 1 - right, 2 - both (match)
int solve(int i = 0, int j = 0)
{
  i = min(i, (int)s.size()), j = min(j, (int)t.size());
  if (i == s.size() && j == t.size()) return 0;
  int &ans = memo[i][j];
  if (ans != -1) return ans;

  ans = 0;
  if (i < s.size())
  {
    int curr = solve(i + 1, j);
    if (curr > ans)
      ans = curr, path[i][j] = 0;
  }
  if (j < t.size())
  {
    int curr = max(ans, solve(i, j + 1));
    if (curr > ans)
      ans = curr, path[i][j] = 1;
  }
  if (i < s.size() && j < t.size() && s[i] == t[j])
  {
    int curr = 1 + solve(i + 1, j + 1);
    if (curr > ans)
      ans = curr, path[i][j] = 2;
  }
  return ans;
}

int main()
{
  while (scanf(" %s", ss) != EOF)
  {
    s = string(ss);
    scanf(" %s", ss);
    t = string(ss);
    DEBUG printf("%s - %s\n", s.c_str(), t.c_str());

    memset(memo, -1, sizeof(memo));
    memset(path, -1, sizeof(path));
    int maxSize = solve();
    DEBUG printf("%d\n", maxSize);
    string ans = "";
    for (int i = 0, j = 0; i < s.size() || j < t.size();)
    {
      if (path[i][j] == -1) break;
      else if (path[i][j] == 0) i++;
      else if (path[i][j] == 1) j++;
      else
      {
        ans += s[i];
        i++, j++;
      }
    }
    printf("%s\n", ans.c_str());
  }
  return 0;
}