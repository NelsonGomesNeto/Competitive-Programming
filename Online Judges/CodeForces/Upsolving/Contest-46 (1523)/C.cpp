#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n;
int a[maxN];

vector<stack<int>> ans;
int solve(int i = 0, stack<int> curr = {})
{
  if (i == n) return true;

  if (a[i] == 1)
  {
    curr.push(1);
    if (solve(i + 1, curr))
    {
      ans.push_back(curr);
      return true;
    }
    curr.pop();
  }
  
  while (!curr.empty() && curr.top() != a[i] - 1)
    curr.pop();

  if (curr.empty()) return false;

  curr.top()++;
  if (solve(i + 1, curr))
  {
    ans.push_back(curr);
    return true;
  }

  return false;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    ans.clear();
    int res = solve();
    reverse(ans.begin(), ans.end());

    int i = 0;
    for (auto &s: ans)
    {
      bool first = true;
      stack<int> ss;
      while (!s.empty())
      {
        ss.push(s.top());
        s.pop();
      }
      while (!ss.empty())
      {
        if (!first) printf(".");
        printf("%d", ss.top());
        if (ss.size() == 1)
          assert(ss.top() == a[i++]);
        ss.pop(), first = false;
      }
      printf("\n");
    }
  }
  return 0;
}
