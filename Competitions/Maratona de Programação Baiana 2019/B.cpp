#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e3, maxB = 1e4; int n, budget;

map<string, int> cities; int totalCities = 0;
vector<pair<int, int>> competidors[maxN];

int memo[maxN][maxB + 1];
int solve(int i, int b)
{
  if (i >= totalCities) return(0);
  if (memo[i][b] == -1)
  {
    int ans = 0;
    for (int j = 0; j < competidors[i].size(); j ++)
      if (b - competidors[i][j].first >= 0)
        ans = max(ans, competidors[i][j].second + solve(i + 1, b - competidors[i][j].first));
    ans = max(ans, solve(i + 1, b));
    memo[i][b] = ans;
  }
  return(memo[i][b]);
}

int main()
{
  cities.clear();
  cin >> n >> budget;

  for (int i = 0; i < n; i ++)
  {
    int v, p, prvSize = cities.size(); string c;
    cin >> v >> p >> c;
    if (!cities.count(c)) cities[c] = prvSize;
    competidors[cities[c]].push_back({v, p});
  }
  totalCities = cities.size();
  for (int i = 0; i < totalCities; i ++)
  {
    sort(competidors[i].begin(), competidors[i].end());
    reverse(competidors[i].begin(), competidors[i].end());
  }

  memset(memo, -1, sizeof(memo));
  int ans = solve(0, budget);
  cout << ans;

  return(0);
}