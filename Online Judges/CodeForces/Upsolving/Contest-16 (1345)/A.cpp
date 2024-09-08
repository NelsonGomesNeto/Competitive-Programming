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
    int n, m; scanf("%d %d", &n, &m);
    printf("%s\n", (n >= 2 && m > 2) || (n > 2 && m >= 2) ? "NO" : "YES");
  }
  return 0;
}
