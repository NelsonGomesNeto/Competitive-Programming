#include <stdio.h>

int main()
{
  int revista, ultima = 0, nope = 0;
  while (scanf("%i", &revista) && revista != 0)
  {
    if (revista > ultima)
    {
      ultima = revista;
    }
    if (revista < ultima)
    {
      nope ++;
    }
  }
  if (nope > 0)
  {
    printf("FORA DE ORDEM\n");
  }
  else
  {
    printf("EM ORDEM\n");
  }
  return(0);
}
