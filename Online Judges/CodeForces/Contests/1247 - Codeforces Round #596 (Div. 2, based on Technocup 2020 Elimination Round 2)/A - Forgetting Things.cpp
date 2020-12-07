#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int a, b;
  while (scanf("%d %d", &a, &b) != EOF)
  {
    if (a == 9 && b == 1)
      printf("9 10\n");
    else if (b > a + 1 || b < a)
      printf("-1\n");
    else if (a == b)
      printf("%d0 %d1\n", a, b);
    else
      printf("%d9 %d0\n", a, b);
  }
  return 0;
}
