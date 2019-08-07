#include <bits/stdc++.h>
#define lli long long int
using namespace std;

char s[1000];

int main()
{
  scanf("%s", s);
  reverse(s, s+strlen(s));
  int num = 0;
  for (int i = 0; s[i]; i ++)
    num += (s[i] == '1') ? 1 << i : 0;
  printf("%d\n", num);

  return(0);
}