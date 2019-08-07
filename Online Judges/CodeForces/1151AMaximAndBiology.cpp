#include <bits/stdc++.h>
using namespace std;

const int maxN = 50 + 1;
char s[maxN + 1];

int minDist(char a, char t)
{
  return(min(abs(a - t), (a > t) ? ('Z' - a + t - 'A' + 1) : (a - 'A' + 'Z' - t + 1)));
}

int main()
{
  int n; scanf("%d", &n);
  scanf(" %s", s);

  int ans = 1e9;
  for (int i = 0; i < n - 3; i ++)
    ans = min(ans, minDist(s[i], 'A') + minDist(s[i + 1], 'C') + minDist(s[i + 2], 'T') + minDist(s[i + 3], 'G'));
  printf("%d\n", ans);
  return(0);
}