#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int n, a, x, b, y;

bool willMeet()
{
  while (a != x && b != y)
  {
    if (a == b) return(true);
    a ++, b --;
    if (a == n) a = 0;
    if (b == -1) b = n - 1;
  }
  return(a == b);
}

int main()
{
  scanf("%d %d %d %d %d", &n, &a, &x, &b, &y); a --, x --, b --, y --;
  printf("%s\n", willMeet() ? "YES" : "NO");
  return(0);
}
