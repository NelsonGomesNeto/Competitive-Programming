#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, c, s;
  scanf("%d %d %d", &n, &c, &s); s --;
  int pos = 0, ans = s == 0;
  for (int i = 0, a; i < c; i ++)
  {
    scanf("%d", &a);
    pos += a;
    pos = ((pos % n) + n) % n;
    if (pos == s) ans ++;
  }
  printf("%d\n", ans);

  return(0);
}