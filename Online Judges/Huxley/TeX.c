#include <stdio.h>
#include <string.h>

int main()
{
  char texto[999]; int repeat, ativ = 0;
  while (scanf("%[^\n]", texto) && texto[0] != '_')
  {
    for (repeat = 0; repeat < strlen(texto); repeat ++)
    {
      if (texto[repeat] == '+' && ativ == 0)
      {
        texto[repeat] = '*';
        ativ ++;
      }
      else if (texto[repeat] == '+')
      {
        texto[repeat] = '#';
        ativ = 0;
      }
    }
    printf("%s\n", texto);
    getchar();
  }
  return(0);
}
