#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n, k;
  while (scanf("%d %d", &n, &k) != EOF)
  {
    int fruits[n]; for (int i = 0; i < n; i++) scanf("%d", &fruits[i]);
    sort(fruits, fruits+n);
    int ans = 0;
    for (int i = 0; i < k; i++) ans += fruits[i];
    printf("%d\n", ans);
  }
  return 0;
}