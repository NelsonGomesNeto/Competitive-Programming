#include <stdio.h>
#include <string.h>

int main()
{
  char tipo[20], rad[2]; int repeat, convert, TVh; float preco;
  for (repeat = 0; repeat < 7; repeat ++)
  {
    scanf("%s", &*tipo);
    for (convert = 0; convert < 20; convert ++)
    {
      tipo[convert] = tolower(tipo[convert]);
    }
    if (strcmp(tipo,"rádio") == 0 || strcmp(tipo,"rÁdio") == 0)
    {
      scanf("%s", &*rad);
      for (convert = 0; convert < 2; convert ++)
      {
        rad[convert] = toupper(rad[convert]);
      }
      if (strcmp(rad,"FM") == 0)
      {
        preco += 500;
      }
      else { preco += 300; }
    }
    else if (strcmp(tipo,"tv") == 0)
    {
      scanf("%i", &TVh);
      if (TVh <= 20)
      {
        preco += 1200;
      }
      else { preco += 2000; }
    }
    else if (strcmp(tipo,"revista") == 0)
    {
      preco += 750;
    }
    else
    {
      preco += 1500;
    }
  }
  printf("%.2f\n", preco);
  return(0);
}
