#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int p[maxN], q[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &p[i]); p[i]--;
      q[p[i]] = i;
    }

    for (int i = 0; i < n; i++)
      printf("%d%c", q[i] + 1, i < n - 1 ? ' ' : '\n');
  }
  return 0;
}