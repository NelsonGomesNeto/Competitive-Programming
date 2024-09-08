#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int a, b, c; scanf("%d %d %d", &a, &b, &c);
  if (a == b) printf("%d\n", c);
  else if (a == c) printf("%d\n", b);
  else if (b == c) printf("%d\n", a);
  else printf("0\n");
  return 0;
}