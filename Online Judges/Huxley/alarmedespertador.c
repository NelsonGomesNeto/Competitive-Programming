#include <stdio.h>

int main()
{
  int h1, m1, h2, m2, min;
  while (scanf("%i %i %i %i", &h1, &m1, &h2, &m2)
        && !(h1 == 0 && m1 == 0 && h2 == 0 && m2 == 0))
  {
    if (h2 > h1)
    {
      min = ((h2 - h1) * 60) + (m2 - m1);
    }
    else if (h2 == h1)
    {
      if (m2 > m1)
      {
        min = m2 - m1;
      }
      else
      {
        min = (24 * 60) + (m2 - m1);
      }
    }
    else
    {
      min = (24 * 60) + ((h2 - h1) * 60) + (m2 - m1);
    }
    printf("%i\n", min);
  }
  return(0);
}
