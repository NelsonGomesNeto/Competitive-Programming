#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; i++)
      printf("%d%c", 1, i < n - 1 ? ' ' : '\n');
  }
  return 0;
}
