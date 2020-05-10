#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int k, n;
int a[maxN];
int diff[maxN];

int main()
{
  while (scanf("%d %d", &k, &n) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    for (int i = 1; i < n; i++)
      diff[i - 1] = a[i] - a[i - 1];
    diff[n - 1] = k - a[n - 1] + a[0];

    int s = 0;
    for (int i = 0; i < n; i++)
      s += diff[i];

    printf("%d\n", s - *max_element(diff, diff+n));
  }
  return 0;
}