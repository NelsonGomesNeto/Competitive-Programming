#include <stdio.h>
#include <string.h>

int main()
{
  float preco = 0, total = 0, caro = 0;
  int convert;
  char material[99], materialcaro[99];
  do
  {
    if (preco != 0)
    {
       scanf("%f", &preco);
    }
    if (preco > caro)
    {
      caro = preco;
      strcpy(materialcaro,material);
      convert = 0;
      while (convert <= 99)
      {
        materialcaro[convert] = toupper(materialcaro[convert]);
        convert ++;
      }
    }
    total += preco;
    preco = 1;
    scanf("%s", &*material);
    convert = 0;
    while (convert <= 99)
    {
      material[convert] = tolower(material[convert]);
      convert ++;
    }
  } while (strcmp(material,"fim") != 0);
  printf("%.2f\n%s\n", total, materialcaro);
  return(0);
}
