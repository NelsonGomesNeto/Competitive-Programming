#include <stdio.h>

int main()
{
  int equation[100], i;
  for (i = 0; i < 100; i ++)
    equation[i] = 0;

  int number = 0, pot = 0, degree = 0; char var, sig = 0;
  do
  {
    scanf("%d%c", &number, &var);

    printf("\n<%d, $%c$>\n", number, var);

    if (var != ' ' && var != '\n')
    {
      if (scanf("%c", &sig) && sig == '^')
        scanf("%d%c", &pot, &sig);
      else
        pot = 1;

      printf("$%c$%d>>\n", sig, pot);
    }

    if (pot > degree) degree = pot;

    //if (var != '\n' && sig != '\n')
      equation[pot] += number;

    pot = 0;
  } while (var != '\n' && sig != '\n');

  for (i = 0; i <= degree; i ++)
  {
    if (equation[i] != 0)
      printf("%dt^%d + ", equation[i], i);

  } printf("\n");

  return(0);
}
