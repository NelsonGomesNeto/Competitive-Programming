#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n;
char s[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    scanf(" %s", s);

    int l = -1, r = -1;
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
      {
        int a = 0, b = 0;
        for (int k = i; k <= j; k++)
          a += s[k] == 'a', b += s[k] == 'b';
        if (a == b)
          l = i + 1, r = j + 1;
      }
    printf("%d %d\n", l, r);
  }
  return 0;
}
