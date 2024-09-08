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
    int ans;
    int left = n % 5, right = 5 - (n % 5);
    if (left < right) ans = n - left;
    else ans = n + right;

    printf("%d\n", ans);
  }
  return 0;
}
