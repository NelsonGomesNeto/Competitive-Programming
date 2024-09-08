#include <stdio.h>
#include <string.h>

int main()
{
  int testes, check; scanf("%d", &testes);
  char string[1000000], GoodString[1000000];
  int posi;
  while (testes > 0)
  {
    for (check = 0; check < 1000000; check ++)
    {
      GoodString[check] = '\0';
      string[check] = '\0';
    }
    getchar(); scanf("%[^\n]", string);
    for (check = 0, posi = 0; check < strlen(string); check ++)
    {
      if (string[check] != string[check + 1])
      {
        GoodString[posi] = string[check];
        posi ++;
      }
    }
    printf("%s\n", GoodString);
    testes --;
  }
  return(0);
}
