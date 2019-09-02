#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 100, maxR = 30000; int n, r;
int memo[maxN][maxR + 1];

struct PosProject
{
  int required, delta;
  bool operator<(const PosProject &p) const
  {
    return(required < p.required || (required == p.required && delta > p.delta));
  }
};
vector<PosProject> posProjects;
struct NegProject
{
  int required, delta;
  bool operator<(const NegProject &p) const
  {
    return(required + delta < p.required + p.delta);
  }
};
vector<NegProject> negProjects;

int solve(int i, int rating)
{
  if (i == negProjects.size()) return(0);
  if (memo[i][min(maxR, rating)] == -1)
  {
    int ans = solve(i + 1, rating);
    if (rating >= negProjects[i].required && rating + negProjects[i].delta >= 0)
      ans = max(ans, solve(i + 1, rating + negProjects[i].delta) + 1);
    memo[i][min(maxR, rating)] = ans;
  }
  return(memo[i][min(maxR, rating)]);
}

int main()
{
  while (scanf("%d %d", &n, &r) != EOF)
  {
    posProjects.clear(), negProjects.clear();
    for (int i = 0, a, b; i < n; i ++)
    {
      scanf("%d %d", &a, &b);
      if (b >= 0) posProjects.push_back({a, b});
      else negProjects.push_back({a, b});
    }
    
    sort(posProjects.begin(), posProjects.end());
    int allPos = 0, rating = r;
    for (int i = 0; i < posProjects.size(); i ++)
      if (rating >= posProjects[i].required)
        allPos ++, rating += posProjects[i].delta;

    sort(negProjects.begin(), negProjects.end()); reverse(negProjects.begin(), negProjects.end());
    memset(memo, -1, sizeof(memo));
    int ans = allPos + solve(0, rating);
    printf("%d\n", ans);
  }
  
  return(0);
}