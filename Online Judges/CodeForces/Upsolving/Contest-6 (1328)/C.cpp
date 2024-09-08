#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e4; int n;
char x[maxN + 1], a[maxN + 1], b[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d", &n);
    scanf(" %s", x);

    bool endedTwo = false;
    for (int i = 0; i < n; i++)
    {
      int value = x[i] - '0';
      if (value < 2)
      {
        if (value == 0) a[i] = b[i] = '0';
        else a[i] = '0' + !endedTwo, b[i] = '0' + endedTwo;
        if (value == 1) endedTwo = true;
      }
      else
      {
        if (endedTwo) a[i] = '0', b[i] = '2';
        else a[i] = b[i] = '1';
      }
    }
    a[n] = b[n] = '\0';
    printf("%s\n%s\n", a, b);
  }
  return 0;
}
