#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  map<int, int> vote; int v;
  while (n --)
  {
    scanf("%d", &v);
    if (!vote.count(v)) vote[v] = 1;
    else vote[v] ++;
  }

  int winner, votes = 0;
  for (auto i: vote)
    if (i.second > votes)
    {
      votes = i.second;
      winner = i.first;
    }

  printf("%d\n", winner);

  return(0);
}