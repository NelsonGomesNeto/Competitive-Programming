#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n;
  while (~scanf("%d", &n))
  {
    int ans = n / 100 + (n % 100 != 0);
    printf("%d\n", ans);
  }
  return 0;
}