#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int q; scanf("%d", &q);
  while (q --)
  {
    int n; scanf("%d", &n);
    if (n == 2) printf("%d\n", 2);
    else printf("%d\n", n & 1);
  }
  return 0;
}
