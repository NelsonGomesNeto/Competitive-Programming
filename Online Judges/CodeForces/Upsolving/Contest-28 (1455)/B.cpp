#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int x;
const int maxX = 3e6 + 1;
int req[maxX];

int main()
{
  for (int i = 0; i < maxX; i++) req[i] = maxX;

  int sum = 0;
  for (int i = 0; sum < maxX; i++)
  {
    sum += (i + 1);
    if (sum < maxX)
      req[sum] = i + 1;
  }
  for (int i = maxX - 1; i >= 0; i--)
    if (req[i] != maxX)
    {
      int j = i - 1;
      while (j >= 0 && req[j] == maxX)
        req[j--] = req[i];
      if (i - 1 >= 0)
        req[i - 1] = req[i] + 1;
      i = j + 1;
    }

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &x);
    // printf("%d - %d\n", x, req[x]);
    printf("%d\n", req[x]);
  }
  return 0;
}
