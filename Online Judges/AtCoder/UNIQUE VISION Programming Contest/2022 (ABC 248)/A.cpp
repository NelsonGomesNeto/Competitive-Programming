#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  bool has[10];
  fill(has, has+10, false);
  int a;
  while (~scanf("%1d", &a))
    has[a] = true;
  for (int i = 0; i < 10; ++i)
    if (!has[i])
      printf("%d\n", i);
  return 0;
}