#include <stdio.h>
#include <string.h>

int main()
{
  char string[9999], letra, check; scanf("%[^\n]", string);
  for (letra = 'a'; letra <= 'z'; letra ++)
  {
    for (check = 0; check < strlen(string); check ++)
    {
      if (letra == tolower(string[check]))
      {
        printf("%c\n", letra);
        check = strlen(string);
      }
    }
  }
  return(0);
}
