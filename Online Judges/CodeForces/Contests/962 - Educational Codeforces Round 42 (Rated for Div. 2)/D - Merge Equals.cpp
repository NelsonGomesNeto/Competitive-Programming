#include <bits/stdc++.h>
#define lli long long int
#define DEBUG if(0)
using namespace std;

void printGraph(map<lli, set<lli> > graph)
{
  for (auto u: graph)
  {
    printf("%lld:", u.first);
    for (auto v: u.second)
      printf(" %lld ->", v);
    printf(" ¬\n");
  }
}

void printMap(map<lli, lli> appears)
{

}

void makePair(map<lli, set<lli> >& graph)
{
  for (auto& u: graph)
  {
    while (u.second.size() > 1)
    {
      u.second.erase(u.second.begin());
      lli pos = *u.second.begin();
      u.second.erase(u.second.begin());
      graph[2 * u.first].insert(pos);
      DEBUG printGraph(graph); DEBUG printf("\n");
    }
  }
}

void printArray(map<lli, set<lli> > graph)
{
  map<lli, lli> array;
  for (auto u: graph)
    if (u.second.size() > 0)
      array[*u.second.begin()] = u.first;
  lli first = 0;
  printf("%lld\n", (lli) array.size());
  for (auto i: array)
  {
    printf("%s%lld", first ? " " : "\0", i.second);
    first = 1;
  } printf("\n");
}

int main()
{
  lli n; scanf("%lld", &n);
  lli value;
  map<lli, set<lli> > graph;
  map<lli, lli> appears;
  for (lli i = 0; i < n; i ++)
  {
    scanf("%lld", &value);
    if (!appears.count(value)) appears[value] = 0;
    else appears[value] ++;
    graph[value].insert(i);
  }

  DEBUG printGraph(graph);
  makePair(graph);
  printArray(graph);

  return(0);
}
