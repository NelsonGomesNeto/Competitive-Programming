#include <stdio.h>

void tobin(long int bin, long int vet[], start)
{
  if (bin > 0)
  {
    tobin(bin / 2);
    if (bin % 2 == 0)
    {
      vet[start] = 0;
    }
    else
    {
      vet[start] = 1;
    }
  }
}

int main()
{
  long int num, binar[999], from = 0; scanf("%ld", &num);
  if (num == 0)
  {
    vet[0] = 0;
  }
  else
  {
    tobin(num, binar[], from);
  }
  return(0);
}
