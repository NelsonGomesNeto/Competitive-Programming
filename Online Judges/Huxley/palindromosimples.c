#include <stdio.h>
#include <stdlib.h>

int main()
{
  char string;
  int i, a = 0, b = 0, c = 0, yes = 0;
  for (i = 0; i < 5; i ++)
  {
    scanf("%c", &string);
    if (string == 'a')
    {
      a ++;
    }
    if (string == 'b')
    {
      b ++;
    }
    if (string == 'c')
    {
      c ++;
    }
    getchar();
  }
  if (a == 2 && b == 2)
  {
    printf("sim\n");
  }
  else if (a == 2 && c == 2)
  {
    printf("sim\n");
  }
  else if (b == 2 && c == 2)
  {
    printf("sim\n");
  }
  else if ((a == 3 && b == 2) || (a == 2 && b == 3))
  {
    printf("sim\n");
  }
  else if ((a == 3 && c == 2) || (a == 2 && c == 3))
  {
    printf("sim\n");
  }
  else if ((b == 3 && c == 2) || (c == 3 && b == 2))
  {
    printf("sim\n");
  }
  else if (a == 5 || b == 5 || c == 5)
  {
    printf("sim\n");
  }
  else if (a == 4 || b == 4 || c == 4)
  {
    printf("sim\n");
  }
  else
  {
    printf("nao\n");
  }
  return(0);
}
