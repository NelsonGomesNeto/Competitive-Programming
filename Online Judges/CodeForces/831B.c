#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
  char layout[2][30], c, string[2000];
  scanf("%s\n", layout[0]);
  int i;
  for (i = 0; i < 26; i ++)
  {
    scanf("%c", &c);
    layout[1][layout[0][i] - 'a'] = c;
  }

  scanf("\n%[^\n]", string);
  int size = strlen(string);
  for (i = 0; i < size; i ++)
  {
    if (toupper(string[i]) >= 'A' && toupper(string[i]) <= 'Z')
    {
      if (string[i] >= 'A' && string[i] <= 'Z')
        printf("%c", toupper(layout[1][tolower(string[i]) - 'a']));
      else
        printf("%c", layout[1][tolower(string[i]) - 'a']);
    }
    else
      printf("%c", string[i]);
  }
  printf("\n");
  
  return(0);
}
