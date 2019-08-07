#include <stdio.h>

int main()
{
  int red, blue; scanf("%d %d", &red, &blue);
  int colorful, nhe;
  if (red < blue)
  {
    colorful = red;
    nhe = (blue - colorful) / 2;
  }
  else
  {
    colorful = blue;
    nhe = (red - colorful) / 2;
  }
  printf("%d %d\n", colorful, nhe);

  return(0);
}