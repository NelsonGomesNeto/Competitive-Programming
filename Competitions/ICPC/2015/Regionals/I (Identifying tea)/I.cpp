#include <bits/stdc++.h>
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  int ans = 0;
  for (int i = 0, a; i < 5; i ++)
  {
    scanf("%d", &a);
    ans += a == t;
  }
  printf("%d\n", ans);
  return(0);
}