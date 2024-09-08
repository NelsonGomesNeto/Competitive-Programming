#include <stdio.h>

int main()
{
  int hour, hourc, minute;
  scanf("%i\n %i", &hour, &minute);
  if (hour > 12)
  {
    hourc = hour - 12;
    printf("%02i\n%02i\npm\n", hourc, minute);
  }
  else if (hour == 0)
  {
    hourc = hour + 12;
    printf("%02i\n%02i\nam\n", hourc, minute);
  }
  else if (hour == 12)
  {
    hourc = hour;
    printf("%02i\n%02i\npm\n", hourc, minute);
  }
  else
  {
    hourc = hour;
    printf("%02i\n%02i\nam\n", hourc, minute);
  }
  return(0);
}
