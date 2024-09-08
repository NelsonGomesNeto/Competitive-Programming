#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int x, y;
  while (~scanf("%d %d", &x, &y))
  {
    if (x > y) swap(x, y);
    printf("%s\n", y - x < 3 ? "Yes" : "No");
  }
  return 0;
}