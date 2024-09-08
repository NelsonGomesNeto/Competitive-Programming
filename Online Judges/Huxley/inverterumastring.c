#include <stdio.h>
#include <string.h>

int main()
{
  char string[266], letra; int repeat, conta = 0;
  scanf("%[^\n]", string);
  for (repeat = 0; repeat < strlen(string); repeat ++)
  {
    if (string[repeat] == letra)
    {
      conta ++;
    }
  }
  for (repeat = strlen(string) - 1; repeat > 0; repeat --)
  {
    printf("%c", string[repeat]);
  }
  printf("%c\n", string[repeat]);
  return(0);
}
