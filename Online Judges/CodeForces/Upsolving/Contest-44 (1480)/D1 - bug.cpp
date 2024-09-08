#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
int a[maxN];

void makeUnique(vector<int> &arr)
{
  arr.resize(distance(arr.begin(), unique(arr.begin(), arr.end())));
}
int currBest = 0;
vector<vector<int>> best;
int solve(int i, vector<vector<int>> curr)
{
  if (i == n)
  {
    makeUnique(curr[0]);
    makeUnique(curr[1]);
    if (curr[0].size() + curr[1].size() > currBest)
      best = curr, currBest = curr[0].size() + curr[1].size();
    return curr[0].size() + curr[1].size();
  }

  int ans = 0;
  curr[0].push_back(a[i]);
  ans = max(ans, solve(i + 1, curr));
  curr[0].pop_back();

  curr[1].push_back(a[i]);
  ans = max(ans, solve(i + 1, curr));
  curr[1].pop_back();

  return ans;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    vector<vector<int>> curr(2, vector<int>());
    int res = solve(0, curr);

    DEBUG
      for (int i = 0; i < 2; i++)
      {
        printf("\t");
        for (int j = 0; j < best[i].size(); j++)
          printf("%d ", best[i][j]);
        printf("\n");
      }

    printf("%d\n", res);
  }
  return 0;
}
