#include <stdio.h>
#include <string.h>

int main()
{
  char string[60], letra; int repeat, conta = 0;
  scanf("%[^\n]", string);
  getchar();
  scanf("%c", &letra);
  for (repeat = 0; repeat < strlen(string); repeat ++)
  {
    if (string[repeat] == letra)
    {
      conta ++;
    }
  }
  printf("%d\n", conta);
  return(0);
}
