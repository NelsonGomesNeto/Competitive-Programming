#include <stdio.h>

struct pao
{
  int tam, divi;
};

int main()
{
  int pessoas, paes, i; scanf("%d %d", &pessoas, &paes);
  struct pao p[paes]; int copy[paes];
  for (i = 0; i < paes; i ++)
  {
    scanf("%d", &p[i].tam);
    copy[i] = p[i].tam; p[i].divi = 2;
  }
  int selected[pessoas], best, pos, quanti = 0;
  while (quanti < pessoas)
  {
    best = 0;
    for (i = 0; i < paes; i ++)
    {
      if (copy[i] > best)
      {
        best = copy[i]; pos = i;
      }
    }
    selected[quanti] = best;
    copy[pos] = p[pos].tam / p[pos].divi;
    p[pos].divi ++; quanti ++;
  }
  printf("%d\n", selected[quanti - 1]);
  return(0);
}
