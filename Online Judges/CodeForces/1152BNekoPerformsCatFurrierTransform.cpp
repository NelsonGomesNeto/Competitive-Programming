#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int getSize(lli number)
{
  int s = 0;
  while (number) number >>= 1, s ++;
  return(s);
}

const int maxX = 4e6;
lli x, numberSize;
bool visited[maxX + 1][2];
set<lli> visitedBig[2];
vector<int> n;
int t;

bool solve(int i, lli number)
{
  if (i > 40) return(false);
  if (number == ((1LL << getSize(number)) - 1))
  {
    t = i;
    return(true);
  }
  if ((number <= maxX && visited[number][(i & 1) == 0])
  || (number > maxX && visitedBig[(i & 1) == 0].count(number))) return(false);
  if (number <= maxX)
    visited[number][(i & 1) == 0] = true;
  else
    visitedBig[(i & 1) == 0].insert(number);
  if (i & 1) return(solve(i + 1, number + 1));
  // for (int j = 0; j <= numberSize; j ++)
  for (int j = getSize(number); j >= 0; j --)
    if (solve(i + 1, number ^ ((1LL << j) - 1)))
    {
      n.push_back(j);
      return(true);
    }
  return(false);
}

int main()
{
  scanf("%lld", &x);

  solve(0, x);
  reverse(n.begin(), n.end());
  printf("%d\n", t);
  if (n.size())
  {
    for (int i: n) printf("%d ", i);
    printf("\n");
  }

  return(0);
}