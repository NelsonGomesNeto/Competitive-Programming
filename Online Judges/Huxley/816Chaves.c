#include <stdio.h>

int main()
{
  int lines, i, j = 0;
  scanf("%d\n", &lines);

  int valid = 1, open = 0;
  char c;
  for (i = 0; i < lines; i ++)
  {
    while (scanf("%c", &c) && c != '\n')
    {
      if (c == '{') open ++;
      if (c == '}' && open <= 0) valid = 0;
      if (c == '}' && open > 0) open --;
    }
  }
  if (open != 0) valid = 0;

  printf("%s\n", valid ? "S" : "N");

  return(0);
}