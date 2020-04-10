#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

ldouble a, b, c;

int main()
{
  while (scanf("%Lf %Lf %Lf", &a, &b, &c) != EOF)
    printf("%s\n", a + 2*sqrt(a)*sqrt(b) + b < c ? "Yes" : "No");
  return 0;
}