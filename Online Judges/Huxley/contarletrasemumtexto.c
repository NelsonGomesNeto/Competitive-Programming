#include <stdio.h>
#include <string.h>

int main()
{
  int palavras, check, checkINT, quantidade, wordToCheck;
  scanf("%d", &palavras);
  char string[palavras][99], procura[99];
  for (check = 0; check < palavras; check ++)
  {
    getchar();
    scanf("%[^\n]", string[check]);
  }
  scanf("%s", procura);
  for (check = 0; check < strlen(procura); check ++)
  {
    quantidade = 0; wordToCheck = 0;
    while (wordToCheck < palavras)
    {
      for (checkINT = 0; checkINT < strlen(string[wordToCheck]); checkINT ++)
      {
        if (procura[check] == string[wordToCheck][checkINT])
        {
          quantidade ++;
        }
      }
      wordToCheck ++;
    }
    printf("%c = %d\n", procura[check], quantidade);
  }
  return(0);
}
