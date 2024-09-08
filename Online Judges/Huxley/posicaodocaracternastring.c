#include <stdio.h>
#include <string.h>

int main()
{
  char string[100], letra; int search, nope = 0;
  scanf("%s\n%c", &*string, &letra);
  for (search = 0; search < strlen(string); search ++)
  {
    if (string[search] == letra)
    {
      printf("%i\n", search);
      nope ++; break;
    }
  }
  if (nope == 0) { printf("-1\n"); }
  return(0);
}
