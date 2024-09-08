#include <stdio.h>

int main()
{
  int graphic, IA, encap, inde, structs, fail = 0;
  scanf("%i\n%i\n%i\n%i\n%i", &graphic, &IA, &encap, &inde, &structs);
  if (graphic > 0 || IA > 0)
  {
    if (encap > 0 && inde > 0)
    {
      if (structs > 0)
      {
        printf("AVALIADO\n");
      }
      else
      {
        fail ++;
      }

    }
    else
    {
      fail ++;
    }
  }
  else
  {
    fail ++;
  }
  if (fail > 0)
  {
    printf("0\n");
  }
  return(0);
}
