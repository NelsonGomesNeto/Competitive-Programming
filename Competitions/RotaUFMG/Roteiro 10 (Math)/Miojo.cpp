#include <bits/stdc++.h>
using namespace std;

int solve(int t, int a, int b)
{
  for (int i = 1; i <= b; i ++)
    if ((a * i) % b == t) return(i);
}

int main()
{
  int t, a, b; scanf("%d %d %d", &t, &a, &b);

  int x = solve(t, a, b);
  int y = solve(t, b, a);
  printf("%d\n", min(a*x, b*y));

  return(0);
}