#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 200 + 1, inf = 1e6;
char ss[maxN + 1], tt[maxN + 1];
string s, t, st;

int memo[maxN][maxN][2*maxN]; char path[maxN][maxN][2*maxN];
int solve(int i = 0, int j = 0, int open = 0)
{
  if (i == s.size() && j == t.size() && !open) return 0;
  if (memo[i][j][open] != -1) return memo[i][j][open];

  int ans = inf;
  if (open)
  {
    ans = 1 + solve(i + (i < s.size() && s[i] == ')'), j + (j < t.size() && t[j] == ')'), open - 1);
    path[i][j][open] = ')';
  }
  if (open < s.size() + t.size() && (i < s.size() || j < t.size()))
  {
    int ret = 1 + solve(i + (i < s.size() && s[i] == '('), j + (j < t.size() && t[j] == '('), open + 1);
    if (ret <= ans)
      ans = ret, path[i][j][open] = '(';
  }

  return memo[i][j][open] = ans;
}

int main()
{
  while (scanf(" %s %s", ss, tt) != EOF)
  {
    s = string(ss), t = string(tt);
    DEBUG printf("<%s> - <%s>\n", s.c_str(), t.c_str());

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    DEBUG printf("%d\n", ans);

    st = "";
    for (int i = 0, j = 0, open = 0; !(i == s.size() && j == t.size() && !open);)
    {
      st += path[i][j][open];
      if (path[i][j][open] == ')')
        i += (i < s.size() && s[i] == ')'), j += (j < t.size() && t[j] == ')'), open --;
      else
        i += (i < s.size() && s[i] == '('), j += (j < t.size() && t[j] == '('), open ++;
    }
    printf("%s\n", st.c_str());
  }
  return 0;
}
