#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int c, a;
  while (scanf("%d %d", &c, &a) != EOF)
  {
    int ans = a / (c - 1) + (a % (c - 1) != 0);
    printf("%d\n", ans);
  }

  return 0;
}