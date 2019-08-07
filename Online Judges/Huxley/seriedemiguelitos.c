#include <stdio.h>

int once = 0, ate;
int migue(int n)
{
  if (once == 0)
  {
    ate = n;
    n = 3;
    once ++;
  }
  if (ate == 1)
  {
    return(n);
  }
  ate --;
  //printf("%d\n", n);
  if (ate % 2 == 0 || n == 3)
  {
    n = migue(n + 4);
  }
  else
  {
    n = migue(n + 1);
  }
}

int main()
{
  int num;
  scanf("%d", &num);
  num = migue(num);
  printf("%d\n", num);
  return(0);
}
