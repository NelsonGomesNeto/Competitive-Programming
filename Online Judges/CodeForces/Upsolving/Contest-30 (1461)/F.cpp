#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
int a[maxN];
char ss[4];
string s;

const lli inf = 1e7;
bool done[maxN];
lli memo[maxN];
char path[maxN + 1];
lli solve(int i = 0)
{
  if (i >= n - 1) return i == n - 1 ? a[i] : 0;
  if (done[i]) return memo[i];

  lli ans = -inf;
  for (char op: s)
  {
    if (op == '+')
    {
      lli res = a[i] + solve(i + 1);
      if (res > ans)
        ans = res, path[i] = op;
    }
    else if (op == '*')
    {
      lli res = a[i] * a[i + 1] + solve(i + 2);
      if (res > ans)
        ans = res, path[i] = op;
    }
    else // '-'
    {
      lli res = a[i] - solve(i + 1);
      if (res > ans)
        ans = res, path[i] = op;
    }
  }

  done[i] = true;
  return memo[i] = ans;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);
    scanf(" %s", ss);
    s = string(ss);

    memset(done, false, sizeof(done));
    memset(path, '\0', sizeof(path));
    lli ans = solve();
    string res = "";
    for (int i = 0; i < n; i++)
    {
      char op = path[i];
      if (op == '*')
      {
        res += to_string(a[i]) + '*' + to_string(a[i + 1]);
        i++;
      }
      else
      {
        res += to_string(a[i]) + op;
      }
    }
    DEBUG printf("%lld\n", ans);
    printf("%s\n", res.c_str());
  }
  return 0;
}
