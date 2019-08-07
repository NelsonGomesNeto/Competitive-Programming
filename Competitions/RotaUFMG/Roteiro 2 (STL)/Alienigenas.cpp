#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n;
  while (scanf("%d", &n) && n)
  {
    set<string> specie; string s;
    for (int i = 0; i < n; i ++)
    {
      cin >> s;
      sort(s.begin(), s.end());
      specie.insert(s);
    }
    printf("%d\n", (int) specie.size());
  }
  return(0);
}