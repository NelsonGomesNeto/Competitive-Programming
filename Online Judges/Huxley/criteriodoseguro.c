#include <stdio.h>

int main()
{
  int homen, velho;
  scanf("%i\n%i", &homen, &velho);
  if (homen < 1)
  {
    if (velho > 0)
    {
      printf("1\n");
    }
    else
    {
      printf("0\n");
    }
  }
  else
  {
    printf("0\n");
  }
  return(0);
}
