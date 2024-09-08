#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    int n; scanf("%d", &n);
    int a[n];
    lli es = 0, os = 0;
    for (int i = 0, j = n >> 1, e = 2, o = 1; j < n; i++, j++, e += 2, o += 2)
    {
      a[i] = e, a[j] = o;
      es += e, os += o;
    }

    if (es != os && !(es - os & 1LL))
    {
      a[n - 1] += es - os;
      os += es - os;
    }

    if (es != os) printf("NO\n");
    else
    {
      printf("YES\n");
      for (int i = 0; i < n; i++)
        printf("%d%c", a[i], i < n - 1 ? ' ' : '\n');
    }
  }
  return 0;
}
