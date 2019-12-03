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
    int d, y = 0; char op[20];
    bool valid = true;
    for (int i = 0; i < n; i ++)
    {
      scanf("%d %s", &d, op);
      if ((y == 20000 && strcmp(op, "North")) || (y - d < 0 && !strcmp(op, "North"))) valid = false;
      if ((y == 0 && strcmp(op, "South")) || (y + d > 20000 && !strcmp(op, "South"))) valid = false;
      if (!strcmp(op, "North")) y -= d;
      if (!strcmp(op, "South")) y += d;
    }
    if (y != 0) valid = false;

    printf("%s\n", valid ? "YES" : "NO");
  }
  return 0;
}