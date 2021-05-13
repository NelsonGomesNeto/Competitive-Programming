#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int a, b, c; scanf("%d %d %d", &a, &b, &c);
  printf("%s\n", a*a + b*b < c*c ? "Yes" : "No");
  return 0;
}