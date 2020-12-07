#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3; int n;
int a[maxN];

int acc[maxN + 1];
map<int, vector<pair<int, int>>> blocks;

vector<pair<int, int>> intervalScheduling(vector<pair<int, int>> interval)
{
  sort(interval.begin(), interval.end(), [&](const pair<int, int> &a, const pair<int, int> &b) { return a.second < b.second || (a.second == b.second && a.first < b.first); });
  vector<pair<int, int>> ans;
  ans.push_back(interval[0]);
  for (int i = 1; i < interval.size(); i++)
    if (interval[i].first > ans.back().second)
      ans.push_back(interval[i]);
  return ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    blocks.clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      acc[i + 1] = acc[i] + a[i];
    }

    for (int i = 0; i < n; i++)
      for (int j = i; j < n; j++)
      {
        DEBUG printf("%d %d - %d\n", i, j, acc[j + 1] - acc[i]);
        blocks[acc[j + 1] - acc[i]].push_back({i, j});
      }

    vector<pair<int, int>> ans;
    for (auto b: blocks)
    {
      vector<pair<int, int>> interval = intervalScheduling(b.second);
      if (interval.size() > ans.size())
        ans = interval;
    }

    printf("%d\n", (int)ans.size());
    for (auto &p: ans)
      printf("%d %d\n", p.first + 1, p.second + 1);
  }
  return 0;
}