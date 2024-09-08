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
    int turnsTakahashi = c / b + (c % b != 0);
    int turnsAoki = a / d + (a % d != 0);
    printf("%s\n", turnsTakahashi <= turnsAoki ? "Yes" : "No");
  }
  return 0;
}