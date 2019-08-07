#include <stdio.h>

int main()
{
  int x, y;
  scanf("%i\n%i", &x, &y);
  if (x > y)  {printf("1\n");}
  else        {printf("0\n");}
  if (x == y) {printf("1\n");}
  else        {printf("0\n");}
  if (x < y)  {printf("1\n");}
  else        {printf("0\n");}
  if (x != y) {printf("1\n");}
  else        {printf("0\n");}
  if (x >= y) {printf("1\n");}
  else        {printf("0\n");}
  if (x <= y) {printf("1\n");}
  else        {printf("0\n");}
  return(0);
}
