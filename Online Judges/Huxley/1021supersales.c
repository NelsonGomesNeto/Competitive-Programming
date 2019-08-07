#include <stdio.h>

struct object
{
  int price, weight;
};

void bt(struct object o[], int p[], int i, int objects, int people, int total, int *max)
{
  if (i == people)
  {
    if (total > (*max))
      (*max) = total;
    return;
  }
  int j;
  for (j = 0; j < )
}

int main()
{
  int tests;
  while (tests > 0)
  {
    int objects; scanf("%d", objects);
    struct object o[objects];
    int i;
    for (i = 0; i < objects; i ++)
      scanf("%d %d", &o[i].price, &o[i].weight);

    int people; scanf("%d", &people);
    int p[people];
    for (i = 0; i < people; i ++)
      scanf("%d", &p[i]);


    tests --;
  }
  return(0);
}
