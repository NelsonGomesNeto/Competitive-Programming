#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int n;

vector<string> ans;
string curr;
void solve(int i = 0, int op = 0)
{
  if (ans.size() == n) return;
  if (2*n - i < op) return;
  if (i == 2*n)
  {
    if (op == 0) ans.push_back(curr);
    return;
  }

  curr[i] = '(';
  solve(i + 1, op + 1);

  if (op)
  {
    curr[i] = ')';
    solve(i + 1, op - 1);
  }
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    ans.clear();
    curr = "";
    for (int i = 0; i < 2*n; i++) curr += '*';
    solve();

    for (auto &s: ans)
      printf("%s\n", s.c_str());
  }
  return 0;
}
