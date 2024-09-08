#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n; lli k;
  while (scanf("%d %lld", &n, &k) != EOF)
  {
    int a[n];
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      a[i]--;
    }

    vector<int> aux, cycle;
    bool visited[n]; memset(visited, false, sizeof(visited));
    aux.push_back(0);
    visited[0] = true;
    int loopAt = 0;
    for (int i = a[0]; !visited[i]; i = a[i])
    {
      aux.push_back(i), visited[i] = true;
      if (visited[a[i]]) loopAt = a[i];
    }

    for (int i = 0, act = false; i < aux.size(); i++)
    {
      if (aux[i] == loopAt)
        act = true;
      if (act) cycle.push_back(aux[i]);
    }

    int ans;
    int space = aux.size() - (int)cycle.size();
    if (k <= space)
      printf("%d\n", 1 + aux[k]);
    else
      printf("%d\n", 1 + cycle[(k - space) % cycle.size()]);
  }
  return 0;
}