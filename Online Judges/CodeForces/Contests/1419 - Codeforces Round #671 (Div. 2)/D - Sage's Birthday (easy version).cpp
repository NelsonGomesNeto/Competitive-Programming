#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
int a[maxN];
int ans[maxN];

int main()
{
  int t;
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    sort(a, a+n);
    for (int i = 1, j = 0; i < n; i += 2, j++)
    {
      ans[i] = a[j];
      a[j] = 1e9 + 1;
    }
    sort(a, a+n, less<int>());
    for (int i = 0, j = 0; i < n; i += 2, j++)
      ans[i] = a[j];

    int total = 0;
    for (int i = 1; i + 1 < n; i += 2)
      total += ans[i] < ans[i + 1] && ans[i] < ans[i - 1];
    printf("%d\n", total);
    for (int i = 0; i < n; i++)
      printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}
