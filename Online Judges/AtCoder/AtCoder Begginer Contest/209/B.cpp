#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2; int n, x;
int a[maxN];

int main()
{
  while (~scanf("%d %d", &n, &x))
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    int needed = 0;
    for (int i = 0; i < n; i++)
    {
      needed += a[i];
      if (i & 1) needed -= 1;
    }
    printf("%s\n", needed <= x ? "Yes" : "No");
  }
  return 0;
}