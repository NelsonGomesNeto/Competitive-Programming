#include <stdio.h>

int main()
{
  int size; scanf("%d", &size);
  int read, i, num = 0;
  for (i = 0; i < size; i ++)
  {
    scanf("%1d", &read);
    if (read == 0)
    {
      printf("%d", num);
      num = 0;
    }
    else
      num ++;
  }
  printf("%d\n", num);

  return(0);
}
