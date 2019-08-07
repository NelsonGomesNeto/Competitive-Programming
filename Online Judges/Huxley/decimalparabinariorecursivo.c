#include <stdio.h>

void tobin(long int bin)
{
  if (bin > 0)
  {
    tobin(bin / 2);
    if (bin % 2 == 0)
    {
      printf("0\n");
    }
    else
    {
      printf("1\n");
    }
  }
}

int main()
{
  long int num; scanf("%ld", &num);
  if (num == 0)
  {
    printf("0\n");
  }
  else
  {
    tobin(num);
  }
  return(0);
}
