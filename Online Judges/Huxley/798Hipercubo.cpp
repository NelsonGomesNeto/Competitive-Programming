#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxK = 1024; int k, m;
set<int> graph[maxK];

int countOnes(int num)
{
  int ones = 0;
  while (num)
  {
    ones += num & 1;
    num >>= 1;
  }
  return(ones);
}

int main()
{
  while (scanf("%d %d", &k, &m) != EOF && k)
  {
    int n = log2(k);
    for (int i = 0; i < k; i ++) graph[i].clear();
    bool valid = countOnes(k) == 1;
    for (int i = 0, u, v; i < m; i ++)
    {
      scanf("%d %d", &u, &v);
      graph[u].insert(v), graph[v].insert(u); 
      if (abs(countOnes(u) - countOnes(v)) != 1)
        valid = false;
    }
    for (int i = 0; i < k; i ++)
      if (graph[i].size() != n)
        valid = false;

    printf("%s\n", valid ? "SIM" : "NAO");
  }
  return(0);
}