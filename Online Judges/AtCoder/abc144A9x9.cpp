#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int a, b; scanf("%d %d", &a, &b);
  if (a > 9 || b > 9) printf("-1\n");
  else printf("%d\n", a * b);
  return 0;
}