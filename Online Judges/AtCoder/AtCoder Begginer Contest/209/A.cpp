#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int a, b; scanf("%d %d", &a, &b);
  int ans = max(0, b - a + 1);
  printf("%d\n", ans);
  return 0;
}