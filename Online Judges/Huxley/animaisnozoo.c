#include <stdio.h>
#include <string.h>

char tipo[99], pais[99], continua[15];
float peso, pesoti = 0, media = 0; int tigre = 0, macaco = 0, cobra = 0, convert;

int check()
{
  scanf("%s", &*continua);
  for (convert = 0; convert < 15; convert ++)
  {
    continua[convert] = tolower(continua[convert]);
  }
  if (strcmp(continua,"parar") != 0)
  {
    return(1);
  }
  else
  {
    return(0);
  }
}

int main()
{
  do
  {
    scanf("%s", &*tipo);
    scanf("%f", &peso);
    for (convert = 0; convert <= 99; convert ++)
    {
      tipo[convert] = tolower(tipo[convert]);
    }
    getchar();
    scanf("%[^\n]", pais);
    //fgets(pais, 99, stdin);
    for (convert = 0; convert <= 99; convert ++)
    {
      pais[convert] = tolower(pais[convert]);
    }
    if (strcmp(tipo,"tigre") == 0)
    {
      tigre ++;
      pesoti += peso;
    }
    if (strcmp(tipo,"macaco") == 0)
    {
      macaco ++;
    }
    if (strcmp(tipo,"cobra") == 0 && strcmp(pais,"venezuela") == 0)
    {
      cobra ++;
    }
  } while (check() == 1);
  if (tigre > 0)
  {
    media = pesoti / tigre;
  }
  printf("%i\n%.2f\n%i\n", macaco, media, cobra);
  return(0);
}
