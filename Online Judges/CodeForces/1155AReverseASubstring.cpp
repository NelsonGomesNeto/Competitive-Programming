#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  char s[n + 1]; scanf(" %s", s);
  bool can = false; int lo, hi;
  for (int i = 0; i < n && !can; i ++)
  {
    int start = i;
    while (i + 1 < n && s[i + 1] == s[start]) i ++;
    if (i + 1 < n && s[i + 1] < s[start])
    {
      lo = start, hi = i + 1;
      can = true;
    }
  }
  if (!can) printf("NO\n");
  else printf("YES\n%d %d\n", lo + 1, hi + 1);
  return(0);
}