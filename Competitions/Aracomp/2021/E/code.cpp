#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3;
char s[maxN + 1];

int main()
{
  int n;
  while (~scanf("%d", &n))
  {
    set<string> pokemons;
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", s);
      pokemons.insert(string(s));
    }

    printf("Falta(m) %d pomekon(s).\n", 151 - (int)pokemons.size());
  }
  return 0;
}