#include <bits/stdc++.h>
using namespace std;

int main()
{
  deque<int> r, l; int last = 0, i = 0; char read;
  while (scanf("%c", &read) && read != '\n')
  {
    i ++;
    if (read == 'r')
      r.push_back(i);
    else
      l.push_front(i);
  }

  for (auto i: r)
    printf("%d\n", i);
  for (auto i: l)
    printf("%d\n", i);

  return(0);
}