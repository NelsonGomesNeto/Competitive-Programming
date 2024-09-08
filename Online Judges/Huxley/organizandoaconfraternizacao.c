#include <stdio.h>
#include <string.h>

int main()
{
  char dia[10], local[10];
  int vota, convert, sexta = 0, domingo = 0, praia = 0, bar = 0;
  for (vota = 0; vota < 11; vota ++)
  {
    scanf("%s\n%s", &*dia, &*local);
    for (convert = 0; convert < 10; convert ++)
    {
      dia[convert] = tolower(dia[convert]);
      local[convert] = tolower(local[convert]);
    }
    if (strcmp(dia,"sexta") == 0) { sexta ++; }
    else { domingo ++; }
    if (strcmp(local,"praia") == 0) { praia ++; }
    else { bar ++; }
  }
  if (sexta > domingo)
  {
    if (praia > bar)
    {
      printf("SEXTA\nPRAIA\n");
    }
    else
    {
      printf("SEXTA\nBAR\n");
    }
  }
  else
  {
    if (praia > bar)
    {
      printf("DOMINGO\nPRAIA\n");
    }
    else
    {
      printf("DOMINGO\nBAR\n");
    }
  }
  return(0);
}
