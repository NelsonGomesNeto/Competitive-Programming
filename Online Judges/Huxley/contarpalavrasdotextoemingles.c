#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
  char word[1000000]; int conta = 0, look, check;
  scanf("%[^\n]", word);
  for (look = 0; look < strlen(word); look ++)
  {
    if ((isalpha(word[look])))
    {
      conta ++;
      while (isalpha(word[look]))
      {
        look ++;
      }
    }
  }
  printf("%d\n", conta);
  return(0);
}
