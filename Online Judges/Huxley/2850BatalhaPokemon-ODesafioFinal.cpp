#include <bits/stdc++.h>
#define lli long long int
using namespace std;

struct Pokemon
{
  char name[100];
  int id, power, hp;
  bool operator<(const Pokemon &p) const
  {
    return(power < p.power || (power == p.power && id > p.id));
  }
};
Pokemon red, blue;

void read(Pokemon &best)
{
  Pokemon aux;
  for (int i = 0; i < 6; i ++)
  {
    scanf(" %s\n%d\n%d\n%d", aux.name, &aux.id, &aux.power, &aux.hp);
    best = max(best, aux);
  }
}

int main()
{
  read(red);
  read(blue);

  printf("Pokemon do Red: %s\n", red.name);
  printf("Pokemon do Blue: %s\n", blue.name);
  int redTurns = ceil((double) blue.hp / red.power), blueTurns = ceil((double) red.hp / blue.power);
  if (redTurns == blueTurns) printf("Empate\n");
  else printf("Vencedor: %s\n", redTurns < blueTurns ? "Red" : "Blue");

  return(0);
}