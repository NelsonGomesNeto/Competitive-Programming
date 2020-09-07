#include <bits/stcd++.h>
using namespace std;
const int maxN = 1e5;

class Solution
{
public:
  int memo[maxN][30];
  int solve(string &s, vector<int> &cost, int i = 0, char prv = 'z' + 1)
  {
    if (i == s.size())
      return 0;
    if (memo[i][prv - 'a'] != -1)
      return memo[i][prv - 'a'];

    int ans = solve(s, cost, i + 1, prv) + cost[i];
    if (prv != s[i])
      ans = min(ans, solve(s, cost, i + 1, s[i]));
    return memo[i][prv - 'a'] = ans;
  }

  int minCost(string s, vector<int> &cost)
  {
    memset(memo, -1, sizeof(memo));
    int ans = solve(s, cost, 0);
    return ans;
  }
};