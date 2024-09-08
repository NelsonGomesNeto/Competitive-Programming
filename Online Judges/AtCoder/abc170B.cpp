#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int x, y;
  while (scanf("%d %d", &x, &y) != EOF)
  {
    bool can = true;
    int b = (y - 2*x) / 2;
    if (((y - 2*x) & 1) || b < 0) can = false;
    if (x - b < 0) can = false;
    printf("%s\n", can ? "Yes" : "No");
  }
  return 0;
}