#include <stdio.h>
#include <string.h>

int main()
{
  char string[999]; int convert;
  while (scanf("%[^\n]", string) && strcmp(string,"the end!") != 0)
  {
    for (convert  = 0; convert < strlen(string); convert ++)
    {
      string[convert] = toupper(string[convert]);
    }
    printf("%s\n", string);
    getchar();
  }
  return(0);
}
