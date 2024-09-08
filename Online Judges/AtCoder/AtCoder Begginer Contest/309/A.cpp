#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int a, b;
  while (~scanf("%d %d", &a, &b))
  {
    int aa = (a - 1) / 3, bb = (b - 1) / 3;
    bool ans = aa == bb;
    printf("%s\n", ans ? "Yes" : "No");
  }
  return 0;
}
