#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
  setlocale(LC_ALL,"");
  int tamanho = 0, repeat = 0, palavra = 0; wchar_t word[266];
  scanf("%ls", (word));
  while (word[repeat] != '\0')
  {
    palavra ++;
    word[repeat] = tolower(word[repeat]);
    repeat ++;
  }
  for (repeat = 0; repeat < palavra / 2; repeat ++)
  {
    if (word[repeat] != word[palavra - (repeat + 1)])
    {
      printf("NAO\n");
      return(0);
    }
    else
    {
      tamanho ++;
    }
  }
  printf("SIM\n%d\n", tamanho);
  return(0);
}
