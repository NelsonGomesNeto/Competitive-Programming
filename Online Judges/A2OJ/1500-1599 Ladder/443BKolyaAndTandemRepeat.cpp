#include <bits/stdc++.h>
using namespace std;

const int maxSize = 200; int k;
char s[2*maxSize + 1];

int main()
{
  scanf("%s\n%d", s, &k);
  for (int i = strlen(s), a = 0; a < k; i ++, a ++) s[i] = '?';

  int sSize = strlen(s);
  int sSized2 = sSize >> 1, best = 0;
  for (int i = 1; i <= sSized2; i ++)
    for (int start = 0; start < sSize; start ++)
    {
      if (start + 2*i > sSize) break;
      bool valid = true;
      for (int p = start, a = 0; a < i; a ++, p ++)
        if (s[p] != '?' && s[p + i] != '?' && s[p] != s[p + i])
          valid = false;
      if (valid) best = 2*i;
    }

  printf("%d\n", best);

  return(0);
}