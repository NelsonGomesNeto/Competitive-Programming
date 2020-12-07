#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

const int maxN = 1e5, maxM = 2e5; int n, m;
pair<int, int> points[maxM];
vector<int> circle[maxN];

int dist(int lo, int hi)
{
  return(min(hi - lo + 1, n - hi + lo + 1));
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i ++)
  {
    scanf("%d %d", &points[i].first, &points[i].second);
    if (points[i].first > points[i].second) swap(points[i].first, points[i].second);
    circle[points[i].first - 1].push_back(dist(points[i].first, points[i].second));
    circle[points[i].second - 1].push_back(dist(points[i].first, points[i].second));
  }
  for (int i = 0; i < n; i ++) sort(circle[i].begin(), circle[i].end());
  DEBUG for (int i = 0; i < n; i ++)
  {
    if (circle[i].size() == 0) continue;
    printf("%d: ", i);
    for (int j = 0; j < circle[i].size(); j ++) printf("%d%c", circle[i][j], j < circle[i].size() - 1 ? ' ' : '\n');
  }

  vector<int> divisors;
  for (int i = 2, end = ceil(sqrt(n)); i <= end; i ++)
    if (n % i == 0)
    {
      divisors.push_back(i);
      if (n / i != i) divisors.push_back(n / i);
    }

  bool can = false;
  for (int i: divisors)
  {
    int space = n / i; bool c = true;
    for (int j = 0; j < i - 1 && c; j ++)
      for (int k = 0; k < space && c; k ++)
        if (circle[space*j + k] != circle[space*(j + 1) + k])
          c = false;
    can = c;
    if (can) break;
  }
  printf("%s\n", can ? "Yes" : "No");

  return(0);
}