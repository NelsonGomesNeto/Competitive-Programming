#include <stdio.h>
#include <string.h>

int main()
{
  char string[999999], sub[999999];
  int tam = 0, check, vezes = 0;
  scanf("%[^\n]", string);
  getchar(); scanf("%[^\n]", sub);
  //printf("%s ~ %s\n", string, sub);
  for (check = 0; check < strlen(string); check ++)
  {
    //printf("%c ~ %c\n", string[check], sub[tam]);
    if (string[check] == sub[tam])
    {
      tam ++;
      if (tam == (int) strlen(sub))
      {
        vezes ++;
        tam = 0;
      }
    }
    else
    {
      if (string[check] == sub[tam - 1])
      {
        tam = 1;
      }
      else
      {
        tam = 0;
      }
    }
  }
  printf("%d\n", vezes);
  return(0);
}
