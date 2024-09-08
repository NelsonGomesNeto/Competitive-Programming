#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
int a[maxN], b[maxN];

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);
    for (int i = 0; i < n; i++)
      scanf("%d", &b[i]);

    bool can = a[0] == b[0];
    bool hasOne = a[0] == 1, hasNeg = a[0] == -1;
    for (int i = 1; i < n; i++)
    {
      if (b[i] - a[i] > 0 && !hasOne) can = false;
      if (b[i] - a[i] < 0 && !hasNeg) can = false;
      if (a[i] == 1) hasOne = true;
      if (a[i] == -1) hasNeg = true;
    }
    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
