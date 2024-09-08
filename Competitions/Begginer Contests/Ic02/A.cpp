#include <bits/stdc++.h>
using namespace std;

int main()
{
  int tests, run = 0; scanf("%d", &tests);
  int posi[99999], i = 0, j = 0; char array[99999][50];
  while (tests > 0)
  {
    if (run > 0)
    {
      printf("\n");
    }
    char sp; i = 0; j = 0;
    while (scanf("%d%c", &posi[i], &sp) && sp == ' ')
    {
      i ++;
    }
    for (j = 0; j <= i; j ++)
    {
      getchar();
      scanf("%s", array[posi[j] - 1]);
    }
    for (j = 0; j <= i; j ++)
    {
      printf("%s\n", array[j]);
    }
    tests --; run ++;
  }
  return(0);
}
