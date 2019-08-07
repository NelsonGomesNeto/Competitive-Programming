#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int num[99], tamanho = 0; char string[99], *ponteiro;

int main()
{
  scanf("%s", &*string);
  ponteiro = strtok(string,",");
  while (ponteiro != NULL)
  {
    num[tamanho] = atoi(ponteiro);
    if (num[tamanho] < num[tamanho - 1])
    {
      printf("NAO\n");
      return(0);
    }
    ponteiro = strtok('\0',",");
    tamanho ++;
  }
  printf("SIM\n");
  return(0);
}
//atoi(strtok(string,",") atoi changes string to int and strtok gets the string until ","
//atoi(strtok('\0',",") atoi changes string to int and strtok get the string from '\0' until ","
