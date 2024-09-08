#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  set<int> a = {1, 2};
  auto it = a.begin();
  printf("%p %p %p\n", --it, a.begin(), a.end());
  return 0;
}