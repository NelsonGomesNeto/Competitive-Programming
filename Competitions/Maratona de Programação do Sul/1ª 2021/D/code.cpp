#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 4e3, maxW = 1e4;
const int inf = 1e9;
int h, c, s, p, w; int n;
vector<int> sizes;
vector<int> delta;
vector<int> qualities, weights;

int readDouble()
{
  int a, b; scanf("%d.%d", &a, &b);
  return a*10 + b;
}

int memo[4][maxW];
int solve(int i = 0, int currW = 0)
{
  if (currW > w) return -inf;
  if (i == 4) return 0;
  int &ans = memo[i][currW];
  if (ans != -1) return ans;

  ans = solve(i + 1, currW);
  for (int j = 0; j < sizes[i]; j++)
    ans = max(ans, solve(i + 1, currW + weights[j + delta[i]]) + qualities[j + delta[i]]);
  return ans;
}

int main()
{
  while (~scanf("%d %d %d %d", &h, &c, &s, &p))
  {
    w = readDouble();
    for (int n: {h, c, s, p})
    {
      for (int i = 0; i < n; i++) qualities.push_back(readDouble());
      for (int i = 0; i < n; i++) weights.push_back(readDouble());
    }
    n = h + c + s + p;
    sizes = {h, c, s, p};
    delta.clear();
    delta.push_back(0);
    for (int i = 0; i < 3; i++)
      delta.push_back(delta.back() + sizes[i]);

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d.%d\n", ans / 10, ans % 10);
  }
  return 0;
}