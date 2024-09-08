//Codigo de exemplo
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int main()
{
  int x[2][2], y[2][2], i;
  for (i = 0; i < 2; i ++)
    scanf("%d %d %d %d", &x[i][0], &y[i][0], &x[i][1], &y[i][1]);


  if (x[0][1] < x[1][0] || x[0][0] > x[1][1]
   || y[0][1] < y[1][0] || y[0][0] > y[1][1])
    printf("0\n");
  else
    printf("1\n");
}
