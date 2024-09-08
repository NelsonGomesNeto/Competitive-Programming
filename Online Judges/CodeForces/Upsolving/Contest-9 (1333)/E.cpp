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
    if (n <= 2) printf("-1\n");
    else
    {
      for (int i = 0, a = 1; i < n; i++)
        for (int j = 0; j < n; j++, a++)
          printf("%d%c", a, j < n - 1 ? ' ' : '\n');
    }
  }
  return 0;
}
/*

*/