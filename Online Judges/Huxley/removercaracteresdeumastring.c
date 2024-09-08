#include <stdio.h>
#include <string.h>

int main()
{
  char word[90], tira[90]; int repeat, tirando;
  scanf("%[^\n]", word);
  getchar();
  scanf("%[^\n]", tira);
  for (repeat = 0; repeat < strlen(word); repeat ++)
  {
    for (tirando = 0; tirando < strlen(tira); tirando ++)
    {
      if (word[repeat] == tira[tirando])
      {
        word[repeat] = ' ';
      }
    }
  }
  for (repeat = 0; repeat < strlen(word); repeat ++)
  {
    if (word[repeat] != ' ')
    printf("%c", word[repeat]);
  }
  printf("\n");
  return(0);
}
