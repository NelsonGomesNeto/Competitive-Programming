#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  map<string, int> aa;
  string a[n];
  for (int i = 0; i < n; i ++)
  {
    cin >> a[i];
    if (!aa.count(a[i]))
      aa[a[i]] = 1;
    else
      aa[a[i]] ++;
  }

  int s = 0; string b;
  for (int i = 0; i < n; i ++)
  {
    cin >> b;
    if (!aa.count(b))
      s ++;
    else
    {
      if (aa[b] <= 0) s ++;
      aa[b] --;
    }
  }

  printf("%d\n", s);
  return(0);
}