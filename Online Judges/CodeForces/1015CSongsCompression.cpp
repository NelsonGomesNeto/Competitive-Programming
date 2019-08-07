#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  pair<int, pair<int, int> > songs[n]; int a, b; lli comp = 0, decomp = 0;
  for (int i = 0; i < n; i ++)
  {
    scanf("%d %d", &a, &b);
    songs[i] = {a - b, {a, b}};
    comp += b; decomp += a;
  }
  sort(songs, songs+n);

  if (comp > m)
    printf("-1\n");
  else
  {
    int compressed = 0;
    for (int i = n - 1; decomp > m; i --, compressed ++)
      decomp -= songs[i].first;
    printf("%d\n", compressed);
  }

  return(0);
}
