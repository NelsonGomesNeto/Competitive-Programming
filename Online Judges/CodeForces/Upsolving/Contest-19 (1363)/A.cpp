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
    int n, x; scanf("%d %d", &n, &x);
    int oddCnt = 0, evenCnt = 0;
    for (int i = 0; i < n; i++)
    {
      int a; scanf("%d", &a);
      oddCnt += a & 1, evenCnt += !(a & 1);
    }

    bool can = false;
    x -= min(x - 1, evenCnt);
    if ((x & 1) && oddCnt >= x) can = true;
    else if (oddCnt > x && evenCnt) can = true;
    printf("%s\n", can ? "Yes" : "No");
  }
  return 0;
}
