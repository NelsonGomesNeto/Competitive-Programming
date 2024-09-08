#include <stdio.h>
#include <string.h>

int main()
{
  char nome[10][20], letra; int repeat, convert;
  for (repeat = 0; repeat < 10; repeat ++)
  {
    scanf("%s", &*nome[repeat]);
    /*for (convert = 0; convert < strlen(nome[repeat]); convert ++)
    {
      nome[repeat][convert] = tolower(nome[repeat][convert]);
    }*/
  }
  getchar();
  scanf("%c", &letra);
  for (repeat = 0; repeat < 10; repeat ++)
  {
    for (convert = 0; convert < strlen(nome[repeat]); convert ++)
    {
      if (nome[repeat][convert] == tolower(letra) || nome[repeat][convert] == toupper(letra))
      {
        printf("%s\n", nome[repeat]);
      }
    }
  }
  return(0);
}
