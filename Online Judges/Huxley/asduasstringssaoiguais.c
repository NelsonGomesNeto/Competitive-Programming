#include <stdio.h>
#include <string.h>

int main()
{
  char word1[60], word2[60];
  scanf("%[^\n]", word1);
  getchar(); scanf("%[^\n]", word2);
  if (strcmp(word1,word2) == 0)
  {
    printf("IGUAIS\n");
  }
  else
  {
    printf("DIFERENTES\n");
  }
  return(0);
}
