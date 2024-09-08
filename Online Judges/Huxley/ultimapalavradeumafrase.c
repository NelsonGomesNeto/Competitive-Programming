#include <stdio.h>
#include <string.h>

int main()
{
  char word[410]; int repeat, from;
  scanf("%[^\n]", word);
  for (repeat = strlen(word) - 1; word[repeat] != ' ' || repeat == 0; repeat --)
  {
  }
  if (repeat > 0)
  {
    from = repeat + 1;
    for (; from < strlen(word); from ++)
    {
      printf("%c", word[from]);
    }
  }
  else
  {
    printf("%s", word);
  }
  printf("\n");
  return(0);
}
