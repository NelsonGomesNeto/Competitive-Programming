#include <stdio.h>
#include <string.h>

int main()
{
  char word[1000000]; int conta = 1, look;
  scanf("%[^\n]", word);
  for (look = 0; look < strlen(word); look ++)
  {
    if (word[look] == ' ' && word[look + 1] != ' ')// || (int) word[look] == 39 && (int) word[look + 1] != 39)
    {
      conta ++;
    }
  }
  printf("%d\n", conta);
  return(0);
}
