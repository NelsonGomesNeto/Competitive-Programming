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
    int p[n];
    for (int i = 0; i < n; i++)
      p[(i + 1) % n] = i + 1;
    for (int i = 0; i < n; i++)
      printf("%d%c", p[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}
