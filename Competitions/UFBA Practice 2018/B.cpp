#include <bits/stdc++.h>
using namespace std;

int main()
{
  char s[2001], t[2001], rt[2001]; scanf("%s\n%s", s, t);
  int ss = strlen(s), tt = strlen(t);
  strcpy(rt, t); reverse(rt, rt+tt);
  int ways = 0;
  for (int i = 0; i + tt - 1 < ss; i ++)
  {
    char done[2]; memset(done, 0, sizeof(done));
    int cant = 0, cant2 = 0;
    for (int j = 0; j < tt && !cant; j ++)
    {
      if (done[t[j] - '0'] && done[t[j] - '0'] != s[i + j]) cant = 1;
      done[t[j] - '0'] = s[i + j];
    }
    memset(done, 0, sizeof(done));
    for (int j = 0; j < tt && !cant2; j ++)
    {
      if (done[rt[j] - '0'] && done[rt[j] - '0'] != s[i + j]) cant2 = 1;
      done[rt[j] - '0'] = s[i + j];
    }
    ways += !cant || !cant2;
  }
  printf("%d\n", ways);
  return(0);
}
