#include <stdio.h>
#include <string.h>
int main()
{
  char word[99], letra; int check;
  scanf("%[^\n]", word);
  getchar();
  scanf("%c", &letra);
  for (check = 0; check < strlen(word); check ++)
  {
    if (letra == word[check])
    {
      printf("%i\n", check);
      check = strlen(word) + 2;
    }
  }
  if (check < strlen(word) + 2)
  {
    printf("-1\n");
  }
  return(0);
}
