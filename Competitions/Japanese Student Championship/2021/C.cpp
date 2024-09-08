#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxX = 2e5 + 1;
int divCount[maxX];

int main()
{
  int a, b;
  while (~scanf("%d %d", &a, &b))
  {
    memset(divCount, 0, sizeof(divCount));
    for (int i = a; i <= b; i++)
    {
      for (int j = 2, end = sqrt(i); j <= end; j++)
        if (i % j == 0)
        {
          divCount[j]++;
          if (i % (i / j) == 0 && j != i / j)
            divCount[i / j]++;
        }
      divCount[i]++;
    }

    int ans = 1;
    for (int i = 2; i < maxX; i++)
      if (divCount[i] > 1)
        ans = i;
    printf("%d\n", ans);
  }
  return 0;
}