#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int m, h;
  scanf("%d %d", &m, &h);
  printf("%s\n", (h % m == 0) ? "Yes" : "No");
  return 0;
}