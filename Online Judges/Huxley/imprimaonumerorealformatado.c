#include <stdio.h>
#include <string.h>
#define is if (numero[pri] == '.' || dec > 0) { dec ++; }
void esp()
{
  int i;
  for (i = 0; i < 6; i ++)
  {
    printf(" ");
  }
}
int main()
{
  int pri, dec; char numero[999]; scanf("%s", numero);
  for (pri = 0, dec = 0; dec <= 2; pri ++)
  {
    if (pri == 0)
    {
      printf("|");
    }
    if (pri < strlen(numero))
    {
      is
      printf("%c", numero[pri]);
    }
    else
    {
      is
      printf("0");
    }
  }
  printf("|\n");
  for (pri = 0, dec = 0; dec <= 5; pri ++)
  {
    if (pri == 0)
    {
      printf("|");
    }
    if (pri < strlen(numero))
    {
      is
      printf("%c", numero[pri]);
    }
    else
    {
      is
      printf("0");
    }
  }
  printf("|\n");
  for (pri = 0, dec = 0; dec <= 1; pri ++)
  {
    if (pri == 0)
    {
      printf("|");
      esp();
    }
    if (pri < strlen(numero))
    {
      is
      printf("%c", numero[pri]);
    }
    else
    {
      is
      printf("0");
    }
  }
  printf("|\n");
  for (pri = 0, dec = 0; dec <= 1; pri ++)
  {
    if (pri == 0)
    {
      printf("|");
    }
    if (pri < strlen(numero))
    {
      is
      printf("%c", numero[pri]);
    }
    else
    {
      is
      printf("0");
    }
  }
  esp();
  printf("|\n");
  return(0);
}
