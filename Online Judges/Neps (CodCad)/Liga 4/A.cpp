#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int a, b, c, d;
  while (scanf("%d %d %d %d", &a, &b, &c, &d) != EOF)
  {
    printf("%s\n", a * b > c * d ? "NERF" : "BUFF");
  }
  return 0;
}