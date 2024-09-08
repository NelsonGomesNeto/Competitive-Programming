#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

// triangle exists iff:
// a < b + c
// a > b - c


int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    int a, b, c, d; scanf("%d %d %d %d", &a, &b, &c, &d);
    printf("%d %d %d\n", b, c, c);
  }
  return 0;
}
