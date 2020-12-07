#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  Notice that we can always make 2^k numbers equal by using the following idea:
    1 2 3 4 ... 2^k // 2^k different numbers
    f(1, 2) f(1, 2) f(3, 4) f(3, 4) ... f(2^k - 1, 2^k) // 2^(k - 1) different numbers
    f(f(1, 2), f(3, 4)) f(f(1, 2), f(3, 4)) f(f(1, 2), f(3, 4)) f(f(1, 2), f(3, 4)) ...
    By the end you will have all 2^k equal, the initial values doesn't matter

  Find the biggest k such that 2^k <= n (notice that 2^k + 2^k > n)
  Use above's idea in the first 2^k numbers, and then use it again in the
  last 2^k numbers.

  Done, you have two different numbers
*/

const int maxN = 15e3; int n;
vector<pair<int, int>> ans;

void solve(vector<pair<int, int>> &curr)
{
  while (curr.size() > 1)
  {
    vector<pair<int, int>> nxt;

    for (int i = 0; i < curr.size(); i += 2)
    {
      for (int j = 0; j < curr[i].second; j++)
        ans.push_back({curr[i].first + j, curr[i + 1].first + j});
      nxt.push_back({curr[i].first, 2*curr[i].second});
    }

    curr = nxt;
  }
}

int main()
{
  int tt = 0;
  while (scanf("%d", &n) != EOF)
  {
    if (tt++) printf("\n");

    int k = 0;
    while (1 << (k + 1) <= n) k++;

    ans.clear();
    // index base, amount
    vector<pair<int, int>> curr;
    for (int i = 0; i < (1 << k); i++)
      curr.push_back({i, 1});
    solve(curr);

    curr.clear();
    for (int i = n - 1, hehe = 0; hehe < (1 << k); hehe++, i--)
      curr.push_back({i, 1});
    reverse(curr.begin(), curr.end());
    solve(curr);

    DEBUG
      for (int i = 0; i < curr.size(); i++)
        printf("\t%d %d\n", curr[i].first, curr[i].second);

    printf("%d\n", (int)ans.size());
    for (auto &p: ans)
      printf("%d %d\n", p.first + 1, p.second + 1);
  }
  return 0;
}