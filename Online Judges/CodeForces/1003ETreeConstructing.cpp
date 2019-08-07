#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, d, k; scanf("%d %d %d", &n, &d, &k);
  vector<int> graph[n];
  if (d >= n || n / k >= d) printf("NO\n");
  else
  {
    int now = n;
    for (int i = 0; i < d; i ++)
    {
      graph[i].push_back(i + 1);
      if (i)
        for (int j = i; j < d; j ++)
        {
          now --;
          if (j == i) graph[i].push_back(now ++);
          else graph[now].push_back(now - 1);
        }
    }
    // int missing = n - d - 1;
    // for (int i = 1; missing; i ++, missing --)
    // {
    //   if (i == d) i = 1;
    //   int canPut = (i <= d / 2) ? i : i - d / 2;
    //   graph[i].push_back(missing + d);
    //   for (int j = 1; j < canPut && missing; j ++, missing --)
    //     graph[missing + d].push_back(missing + d - 1);
    // }

    printf("YES\n"); int done = 0;
    for (int i = 0; i < n; i ++)
      for (auto j: graph[i])
      {
        if (done < n - 1) printf("%d %d\n", i + 1, j + 1);
        done ++;
      }
  }
  return(0);
}
