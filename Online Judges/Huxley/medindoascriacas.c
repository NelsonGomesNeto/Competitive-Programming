#include <stdio.h>
#include <string.h>

char crianco[99], menor[99], maior[99], continua[3];
float H, menorH, maiorH = 0; int first = 0, convert;

int check()
{
  scanf("%s", &*continua);
  for (convert = 0; convert < 3; convert ++)
  {
    continua[convert] = tolower(continua[convert]);
  }
  if (strcmp(continua,"fim") != 0)
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
    if (first > 0) { getchar(); }
    scanf("%[^\n]", &*crianco);
    for (convert = 0; convert < 99; convert ++)
    {
      crianco[convert] = toupper(crianco[convert]);
    }
    scanf("%f", &H);
    if (first == 0) { menorH = H; strcpy(menor,crianco); }
    if (H < menorH) { menorH = H; strcpy(menor,crianco); }
    if (H > maiorH) { maiorH = H; strcpy(maior,crianco); }
    first ++;
  } while (check() == 1);
  printf("%s\n%s\n", menor, maior);
  return(0);
}
