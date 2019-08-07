#include <stdio.h>

int main()
{
  float precoAntes, precoDepois; int viva = 0, repeat;
  for (repeat = 0; repeat < 5; repeat ++)
  {
    scanf("%f\n%f", &precoAntes, &precoDepois);
    if (precoAntes * 0.8 >= precoDepois)
    {
      viva ++;
    }
  }
  printf("%i\n", viva);
  return(0);
}
