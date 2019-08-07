#include <bits/stdc++.h>

int main()
{
  int people, t = 0;
  while (scanf("%d", &people) && people != 0)
  {
    if (t) printf("\n");
    
    int person, winner;
    for (int i = 1; i <= people; i ++)
    {
      scanf("%d", &person);
      if (person == i)
        winner = person;
    }

    printf("Teste %d\n%d\n", ++ t, winner);
  }
  return(0);
}