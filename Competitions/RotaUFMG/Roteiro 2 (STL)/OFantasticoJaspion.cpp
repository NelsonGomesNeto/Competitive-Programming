#include <bits/stdc++.h>
using namespace std;

int main()
{
  int t, r = 0; scanf("%d", &t);
  while (r < t)
  {
    if (r ++) printf("\n");
    int m, n; scanf("%d %d", &m, &n); getchar();
    map<string, string> dict; string a, b;
    for (int i = 0; i < m; i ++)
    {
      getline(cin, a);
      getline(cin, b);
      dict[a] = b;
    }

    char end; int first = 1;
    while (n)
    {
      cin >> a; if (scanf("%c", &end) == EOF) end = '\n';
      if (!dict.count(a))
        cout << a;
      else
        cout << dict[a];
      printf("%c", end);
      if (end == '\n')
        n --;
    }
  }
  return(0);
}