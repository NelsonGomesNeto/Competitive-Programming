#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int b, g, n;
  while (scanf("%d %d %d", &b, &g, &n) != EOF)
  {
    int ans = 0;
    for (int i = 0; i <= n; i ++)
      ans += i <= b && (n - i) <= g;
    printf("%d\n", ans);
  }
  return(0);
}
