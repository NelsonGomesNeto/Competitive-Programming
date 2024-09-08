#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, m; lli r;
int p[2][maxN];

int binarySearch(int target, int lo = 0, int hi = n - 1)
{
  while (lo < hi)
  {
    int mid = (lo + hi) >> 1;
    if (p[0][mid] >= target) hi = mid;
    else lo = mid + 1;
  }
  return p[0][lo] < target ? n : lo;
}

int main()
{
  while (scanf("%d %d %lld", &n, &m, &r) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &p[0][i]);

    sort(p[0], p[0]+n);

    for (int i = 0; i < m; i++)
      p[1][i] = n - binarySearch(i + 1);
    sort(p[0], p[0]+n, greater<int>());
    sort(p[1], p[1]+m, greater<int>());

    int sz = r & 1 ? m : n;
    int side = r & 1;
    for (int i = 0; i < sz; i++)
      printf("%d%c", p[side][i], i < sz - 1 ? ' ' : '\n');
  }
  return 0;
}