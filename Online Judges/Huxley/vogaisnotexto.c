#include <stdio.h>
#include <string.h>

int main()
{
  int repeat, a = 0, e = 0, i = 0, o = 0, u = 0; char frase[300];
  scanf("%[^\n]", frase);
  for (repeat = 0; repeat < strlen(frase); repeat ++)
  {
    frase[repeat] = tolower(frase[repeat]);
    if (frase[repeat] == 'a')
    {
      a ++;
    }
    else if (frase[repeat] == 'e')
    {
      e ++;
    }
    else if (frase[repeat] == 'i')
    {
      i ++;
    }
    else if (frase[repeat] == 'o')
    {
      o ++;
    }
    else if (frase[repeat] == 'u')
    {
      u ++;
    }
  }
  printf("a %d\n", a);
  printf("e %d\n", e);
  printf("i %d\n", i);
  printf("o %d\n", o);
  printf("u %d\n", u);
}
