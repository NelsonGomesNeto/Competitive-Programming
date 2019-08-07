#include <stdio.h>

int main()
{
  char A, B, aux;
  scanf("%c\n%c", &A, &B);
  if (A > B)
  {
    if ((A - B) % 2 == 0)
    {
      printf("%c\n", (A / 2) + 49);
    }
    else
    {
      printf("%c\n%c\n", ((A / 2) + 48), ((A / 2) + 49));
    }
  }
  else
  {
    if ((B - A) % 2 == 0)
    {
      printf("%c\n", (B / 2) + 49);
    }
    else
    {
      printf("%c\n%c\n", ((B / 2) + 48), ((B / 2) + 49));
    }
  }
  return(0);
}
