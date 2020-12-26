#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  bool can = false;
  int n; scanf("%d", &n);
  for (int a = 1; a <= 9; a ++)
    for (int b = 1; b <= 9; b ++)
      if (a * b == n)
        can = true;
  if (!can)
    printf("No\n");
  else
    printf("Yes\n");
  return 0;
}