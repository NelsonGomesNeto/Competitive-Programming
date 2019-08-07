#include <bits/stdc++.h>
using namespace std;

const int maxN = 3e3; int n;
map<int, int> xMap, yMap;

int table[maxN + 1][maxN + 1], sum[maxN + 1][maxN + 1], points[maxN][2], compressedPoints[maxN][2];
set<int> xSet, ySet;
vector<int> xs, ys;

int query(int loi, int loj, int hii, int hij)
{
  return(sum[hii][hij] - sum[loi - 1][hij] - sum[hii][loj - 1] + sum[loi - 1][loj - 1]);
}

int main()
{
  scanf("%d", &n);
  for (int i = 0, x, y; i < n; i ++)
  {
    scanf("%d %d", &x, &y);
    if (!xSet.count(x)) xSet.insert(x), xs.push_back(x);
    if (!ySet.count(y)) ySet.insert(y), ys.push_back(y);
    points[i][0] = x, points[i][1] = y;
  }
  sort(xs.begin(), xs.end()), sort(ys.begin(), ys.end());
  for (int i = 0; i < n; i ++)
  {
    compressedPoints[i][0] = 1 + lower_bound(xs.begin(), xs.end(), points[i][0]) - xs.begin();
    compressedPoints[i][1] = 1 + lower_bound(ys.begin(), ys.end(), points[i][1]) - ys.begin();
    table[compressedPoints[i][1]][compressedPoints[i][0]] ++;
  }

  for (int i = 1; i <= ys.size(); i ++)
    for (int j = 1; j <= xs.size(); j ++)
      sum[i][j] = sum[i][j - 1] + table[i][j];
  for (int j = 1; j <= xs.size(); j ++)
    for (int i = 1; i <= ys.size(); i ++)
      sum[i][j] += sum[i - 1][j];

  int ans = 0;
  for (int i = 0; i < n; i ++)
    for (int j = i + 1; j < n; j ++)
    {
      int a = query(min(compressedPoints[i][1], compressedPoints[j][1]), min(compressedPoints[i][0], compressedPoints[j][0]),
                   max(compressedPoints[i][1], compressedPoints[j][1]), max(compressedPoints[i][0], compressedPoints[j][0]));
      ans += a == 2;
    }
  printf("%d\n", ans);

  return(0);
}