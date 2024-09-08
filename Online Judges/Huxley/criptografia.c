#include <stdio.h>
#include <string.h>

int main()
{
  char aux; int convert, inverso;
  int linhas, repeat; scanf("%d", &linhas);
  char string[linhas][110];
  for (repeat = 0; repeat < linhas; repeat ++)
  {
    getchar();
    scanf("%[^\n]", string[repeat]);
  }
  for (repeat = 0; repeat < linhas; repeat ++)
  {
    for (convert = 0; convert < strlen(string[repeat]); convert ++)
    {
      if (string[repeat][convert] > 64 && !(string[repeat][convert] > 90 && string[repeat][convert] < 97)
          && string[repeat][convert] < 123)
      {
        string[repeat][convert] += 3;
      }
    }

    for (convert = strlen(string[repeat]) - 1, inverso = 0; inverso < convert; convert --, inverso ++)
    {
      aux = string[repeat][inverso];
      string[repeat][inverso] = string[repeat][convert];
      string[repeat][convert] = aux;
    }

    for (convert = (strlen(string[repeat]) / 2); convert < strlen(string[repeat]); convert ++)
    {
      string[repeat][convert] -= 1;
    }
  }
  for (repeat = 0; repeat < linhas; repeat ++)
  {
    printf("%s\n", string[repeat]);
  }
  return(0);
}
//Até 64
