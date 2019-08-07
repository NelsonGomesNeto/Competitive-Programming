#include <stdio.h>

int main()
{
  int comandos, x = 0, y = 0, volta = 1; char move;
  scanf("%i", &comandos);
  while (comandos > 0)
  {
    getchar();
    scanf("%c", &move);
    if (move == 'S' && y <= 190)
    {
      y += 10;
    }
    else if (move == 'F' && x <= 1990 && x >= -1990 && y > 0)
    {
      x += 10 * volta;
    }
    else if (move == 'V' && x <= 1990 && x >= -1990 && y > 0)
    {
      x += 10;
      volta *= (-1);
    }
    else if (move == 'D' && y != 0)
    {
      y -= 10;
    }
    comandos --;
  }
  if (x < 0)
  {
    x *= (- 1);
  }
  printf("%i %i\n", y, x);
  return(0);
}
