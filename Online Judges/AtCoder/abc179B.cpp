#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n;
  while (scanf("%d", &n) != EOF)
  {
    int d[n][2];
    for (int i = 0; i < n; i++)
      for (int j = 0; j < 2; j++)
        scanf("%d", &d[i][j]);

    bool can = false;
    for (int i = 2; i < n; i++)
    {
      bool yes = true;
      for (int j = 0; j < 3; j++)
        if (d[i - j][0] != d[i - j][1])
          yes = false;
      can |= yes;
    }
    printf("%s\n", can ? "Yes" : "No");
  }
  return 0;
}