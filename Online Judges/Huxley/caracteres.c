#include <stdio.h>

int main()
{
  int tamanho, inv;
  while (scanf("%d", &tamanho) && tamanho != 0)
  {
    char word[tamanho]; inv = tamanho;
    getchar();
    scanf("%[^\n]", word);
    while (inv > 1)
    {
      printf("%c", word[inv - 1]);
      inv --;
    }
    printf("%c\n", word[0]);
  }
  return(0);
}
