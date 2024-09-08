//Codigo de exemplo
#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int abso(int a)
{
  return(a < 0 ? -a : a);
}

int main()
{
  int pos[4], i;
  for (i = 0; i < 4; i ++)
    scanf("%d", &pos[i]);

  int cruz = abso(pos[2] - pos[0]) + abso(pos[3] - pos[1]);

  printf("%d\n", cruz);
}
