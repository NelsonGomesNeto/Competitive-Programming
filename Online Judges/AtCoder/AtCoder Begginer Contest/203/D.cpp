#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 800; int n, k;
vector<int> as;
int medianPos;
int a[maxN][maxN];
int b[maxN][maxN];
int acc[maxN + 1][maxN + 1];

int getSum(int loi, int loj, int hii, int hij)
{
  return acc[hii + 1][hij + 1] - acc[loi][hij + 1] - acc[hii + 1][loj] + acc[loi][loj];
}

bool can(lli x)
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      b[i][j] = a[i][j] <= x;

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      acc[i + 1][j + 1] = acc[i][j + 1] + acc[i + 1][j] - acc[i][j] + b[i][j];

  for (int i = 0; i + k - 1 < n; i++)
    for (int j = 0; j + k - 1 < n; j++)
      if (getSum(i, j, i + k - 1, j + k - 1) >= medianPos)
        return true;
  return false;
}

int main()
{
  while (~scanf("%d %d", &n, &k))
  {
    medianPos = ((k * k + 1) >> 1) + 0;

    as.clear();
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
      {
        scanf("%d", &a[i][j]);
        as.push_back(a[i][j]);
      }
    sort(as.begin(), as.end());
    as.resize(distance(as.begin(), unique(as.begin(), as.end())));

    int lo = 0, hi = as.size() - 1;
    while (lo < hi)
    {
      lli mid = (lo + hi) >> 1;
      if (can(as[mid])) hi = mid;
      else lo = mid + 1;
    }
    printf("%d\n", as[lo]);
  }
  return 0;
}