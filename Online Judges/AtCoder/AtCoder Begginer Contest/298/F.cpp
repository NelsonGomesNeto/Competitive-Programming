#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
int n;

map<lli, map<lli, lli>> mat;
map<lli, lli> rows, columns;

pair<lli, lli> findBest(const map<lli, lli>& a)
{
  lli b = a.begin()->first;
  lli bs = a.begin()->second;
  for (const auto [i, sum] : a)
  {
    if (sum > bs)
    {
      bs = sum;
      b = i;
    }
  }
  return make_pair(b, bs);
}

int main()
{
  while (~scanf("%d", &n))
  {
    mat.clear(), rows.clear(), columns.clear();
    for (int q = 0; q < n; ++q)
    {
      lli i, j, x;
      scanf("%lld %lld %lld", &i, &j, &x);
      rows[i] += x;
      columns[j] += x;
      mat[i][j] = x;
    }

    auto [bestRow, bestRowSum] = findBest(rows);
    auto [bestColumn, bestColumnSum] = findBest(columns);

    DEBUG printf("\t%lld %lld\n", bestRow, bestRowSum);

    lli ans = 0;
    for (const auto [j, sum] : columns)
    {
      ans = max(ans, bestRowSum + sum - mat[bestRow][j]);
    }
    for (const auto [i, sum] : rows)
    {
      ans = max(ans, bestColumnSum + sum - mat[i][bestColumn]);
    }
    printf("%lld\n", ans);
  }
  return 0;
}
