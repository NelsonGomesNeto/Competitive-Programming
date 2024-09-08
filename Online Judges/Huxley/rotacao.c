#include <stdio.h>
#include <string.h>

int main()
{
  char string[110][110]; int ler = 0, maior = 0, printar, quanti;
  while (scanf("%[^\n]", string[ler]) != EOF)
  {
    if (strlen(string[ler]) > maior)
    {
      maior = strlen(string[ler]);
    }
    ler ++;
    getchar();
  }
  for (printar = 0; printar < maior; printar ++)
  {
    for (quanti = ler - 1; quanti >= 0; quanti --)
    {
      if (printar < strlen(string[quanti]))
      {
        printf("%c", string[quanti][printar]);
      }
      else
      {
        printf(" ");
      }
    }
    printf("\n");
  }
  return(0);
}
/*Rene Decartes once said,
"I think, therefore I am."*/
