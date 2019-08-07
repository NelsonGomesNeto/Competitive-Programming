#include <stdio.h>
#include <string.h>

int main()
{
  char teste[99];
  int convert;
  scanf("%s", &*teste);
  printf("%s\n", teste);
  for (convert = 0; convert < 99; convert ++)
  {
    teste[convert] = tolower(teste[convert]);
  }
  printf("%s\n", teste);
  for (convert = 0; convert < 99; convert ++)
  {
    teste[convert] = toupper(teste[convert]);
  }
  printf("%s\n", teste);
  for (convert = 0; convert < 99; convert ++)
  {
    teste[convert] = tolower(teste[convert]);
  }
  printf("%s\n", teste);
}
