#include <stdio.h>
#include <string.h>

int main()
{
  char escolha[99];
  int repeat, convert, cinema = 0;
  for (repeat = 0; repeat < 7; repeat ++)
  {
    scanf("%s", &*escolha);
    convert = 0;
    while (convert <= 99)
    {
      escolha[convert] = tolower(escolha[convert]);
      convert ++;
    }
    if (strcmp(escolha,"cinema") == 0)
    {
      cinema ++;
    }
  }
  if (cinema > 3)
  {
    printf("CINEMA\n");
  }
  else
  {
    printf("BOLICHE\n");
  }
  return(0);
}
