#include <stdio.h>
#include <string.h>

void corrige(char string[])
{
  int corr;
  for (corr = 0; corr < strlen(string); corr ++)
  {
    if (string[corr] == ',')
    {
      string[corr] = ' ';
    }
  }
}

int main()
{
  int continua = 1; char cont;
  char criatura[999];
  while (scanf("%s", criatura) != EOF)
  {
    if (continua > 1)
    {
      printf("\n");
    }
    int str, agi, inti, sab; scanf("%d,%d,%d,%d", &str, &agi, &inti, &sab);
    char caracteris[99999]; getchar();
    scanf("%s", caracteris);
    corrige(caracteris);
    char habili[99999];
    scanf("%s", habili);
    corrige(habili);
    printf("Criatura: %s\n", criatura);
    printf("Status:\n");
    printf(" Forca: %d\n", str);
    printf(" Agilidade: %d\n", agi);
    printf(" Intigencia: %d\n", inti);
    printf(" Sabedoria: %d\n\n", sab);
    printf("Caracteristicas:\n%s \n\n", caracteris);
    printf("Habilidades:\n%s \n", habili);
    continua ++;
    if (continua >= 1)
    {
      getchar();
    }
  }
  return(0);
}
