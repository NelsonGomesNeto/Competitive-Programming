#include <bits/stdc++.h>
using namespace std;

int main()
{
  int a, b, c; scanf("%d %d %d", &a, &b, &c);
  int best = 999999;
  for (int i = 1; i <= 100; i ++)
  {
    int needsToWalk = abs(a - i) + abs(b - i) + abs(c - i);
    best = min(best, needsToWalk);
  }
  printf("%d\n", best);
  return(0);
}