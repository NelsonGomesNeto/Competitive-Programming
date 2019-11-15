#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int n, x, a, b; scanf("%d %d %d %d", &n, &x, &a, &b);
    if (a > b) swap(a, b);
    while (x && a > 1) a --, x --;
    while (x && b < n) b ++, x --;
    printf("%d\n", b - a);
  }
  return 0;
}
