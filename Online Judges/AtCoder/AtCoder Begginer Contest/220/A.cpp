#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int a, b, c; scanf("%d %d %d", &a, &b, &c);
  for (int i = a; i <= b; i++)
  {
    if (i % c == 0)
    {
      printf("%d\n", i);
      return 0;
    }
  }
  printf("-1\n");
  return 0;
}