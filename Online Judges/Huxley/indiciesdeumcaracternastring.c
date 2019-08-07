#include <stdio.h>
#include <string.h>

int main()
{
  char word[60], letra; int repeat;
  scanf("%[^\n]", word);
  getchar();
  scanf("%c", &letra);
  for (repeat = 0; repeat < strlen(word); repeat ++)
  {
    if (word[repeat] == letra)
    {
      printf("%d\n", repeat);
    }
  }
  printf("-1\n" );
  return(0);
}
