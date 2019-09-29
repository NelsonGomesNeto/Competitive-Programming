#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n;
  while (scanf("%d", &n) != EOF)
  {
    list<int> bags[n];
    for (int i = 0, lo = 1, hi = n*n; lo < hi; i = (i + 1) % n)
      for (int j = 0; j < n >> 1; j ++)
        bags[i].push_back(lo ++), bags[i].push_back(hi --);
    for (int i = 0; i < n; i ++)
    {
      int j = 0;
      for (int a: bags[i])
        printf("%d%c", a, j ++ < bags[i].size() - 1 ? ' ' : '\n');
    }
  }
  return 0;
}