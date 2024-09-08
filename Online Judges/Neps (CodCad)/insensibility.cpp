//Codigo de exemplo
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int square(int a)
{
  return(a * a);
}

int main()
{
  int tests; scanf("%d", &tests);
  int pos[tests][4], i, j;
  for (i = 0; i < tests; i ++)
    for (j = 0; j < 4; j ++)
      scanf("%d", &pos[i][j]);

  int D = 0;
  for (i = 0; i < tests; i ++)
    D += square(pos[i][0] - pos[i][2]) + square(pos[i][1] - pos[i][3]);

  printf("%d\n", D);
}
