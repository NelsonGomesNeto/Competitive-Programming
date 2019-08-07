#include <stdio.h>
#include <string.h>

int main()
{
  char direcA[10], direcB[10]; int turn = 0, convert;
  scanf("%s %s", direcA, direcB);
  for (convert = 0; convert < 10; convert ++)
  {
    direcA[convert] = tolower(direcA[convert]);
    direcB[convert] = tolower(direcB[convert]);
  }
  if (strcmp(direcA,"norte") == 0)
  {
    turn += 0;
  }
  else if (strcmp(direcA,"sul") == 0)
  {
    turn += 180;
  }
  else if (strcmp(direcA,"leste") == 0)
  {
    turn += 270;
  }
  else if (strcmp(direcA,"oeste") == 0)
  {
    turn += 90;
  }
  if (strcmp(direcB,"norte") == 0)
  {
    turn += 0;
  }
  else if (strcmp(direcB,"sul") == 0)
  {
    turn += 180;
  }
  else if (strcmp(direcB,"leste") == 0)
  {
    turn += 90;
  }
  else if (strcmp(direcB,"oeste") == 0)
  {
    turn += 270;
  }
  if (turn == 360)
  {
    turn = 0;
  }
  if (turn == 270 || turn == 450)
  {
    turn = 90;
  }
  if (turn == 540)
  {
    turn = 180;
  }
  printf("%i\n", turn);
  return(0);
}
//norte = 90
//sul = -90
//leste = 180
