#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e3 + 1; int n;

bool notPrime[maxN], twoPow[maxN];
vector<int> primes;

void handleLoop(int &pos, int &loops)
{
  if (pos > n)
    pos = 0, loops ++;
}

int bonus(int pos, int &loops)
{
  handleLoop(pos, loops);
  if (twoPow[pos]) pos += 2;
  else if (!notPrime[pos]) pos -= 2; // never will be negative
  handleLoop(pos, loops);
  return pos;
}

int main()
{
  for (int i = 0; (1 << i) < maxN; i ++)
    twoPow[1 << i] = true;

  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i < maxN; i ++)
  {
    if (!notPrime[i]) primes.push_back(i);
    for (int j = 0; i * primes[j] < maxN; j ++)
    {
      notPrime[i * primes[j]] = true;
      if (i % primes[j] == 0) break;
    }
  }

  int p; scanf("%d %d", &p, &n);
  for (int pp = 1; pp <= p; pp ++)
  {
    int k; scanf("%d", &k);
    int fPos = 0, aPos = 0, fLoops = 0, aLoops = 0;
    for (int i = 0; i < k; i ++)
    {
      int f, a; scanf("%d %d", &f, &a);
      fPos = bonus(fPos + f, fLoops), aPos = bonus(aPos + a, aLoops);
      DEBUG printf("\t%d %d\n", fPos, aPos);
    }
    printf("Partida %d : ", pp);
    if (fLoops > aLoops || (fLoops == aLoops && fPos > aPos)) printf("Fabio venceu na posicao %d passando %d vezes pelo final do tabuleiro\n", fPos, fLoops);
    else if (aLoops > fLoops || (aLoops == fLoops && aPos > fPos)) printf("Ayalla venceu na posicao %d passando %d vezes pelo final do tabuleiro\n", aPos, aLoops);
    else printf("Houve um empate nas posicoes %d e %d\n", fPos, aPos);
  }
  return 0;
}