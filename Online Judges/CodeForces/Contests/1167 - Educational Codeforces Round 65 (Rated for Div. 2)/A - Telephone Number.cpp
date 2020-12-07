#include <bits/stdc++.h>
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int n; scanf("%d", &n);
    char s[n + 1]; scanf(" %s", s);
    bool has = false; int pos = -1;
    for (int i = 0; s[i]; i ++)
      if (s[i] == '8' && pos == -1) has = true, pos = i;
    printf("%s\n", has && n - pos >= 11 ? "YES" : "NO");
  }
  return(0);
}