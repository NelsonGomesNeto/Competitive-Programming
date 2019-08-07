#include <stdio.h>

int palindrome(int h, int m)
{
  char string[5];
  sprintf(string, "%.2d%.2d", h, m); // Needs this '.'
  return(string[0] == string[3] && string[1] == string[2]);
}

int main()
{
  int h, m; scanf("%d:%d", &h, &m);

  int minutes = 0;
  while (!palindrome(h, m))
  {
    minutes ++;
    m ++;
    if (m > 59)
    {
      m = 0;
      h ++;
    }
    if (h > 23)
      h = 0;
  }

  printf("%d\n", minutes);

  return(0);
}
