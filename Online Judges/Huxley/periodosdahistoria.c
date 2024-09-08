#include <stdio.h>
#include <string.h>

int main()
{
  int ano, convert; char era[2];
  scanf("%i\n%s", &ano, &*era);
  for (convert = 0; convert < 2; convert ++)
  {
    era[convert] = tolower(era[convert]);
  }
  if (strcmp(era,"ac") == 0)
  {
    if (ano >= 4000)
    {
      printf("PRE-HISTORIA\n");
    }
    else
    {
      printf("ANTIGUIDADE\n");
    }
  }
  else
  {
    if (ano <= 476)
    {
      printf("ANTIGUIDADE\n");
    }
    else if (ano <= 1453)
    {
      printf("IDADE MEDIA\n");
    }
    else if (ano <= 1789)
    {
      printf("IDADE MODERNA\n");
    }
    else if (ano > 1789)
    {
      printf("IDADE CONTEMPORANEA\n");
    }
  }
  return(0);
}
