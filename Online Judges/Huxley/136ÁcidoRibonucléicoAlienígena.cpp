#include <bits/stdc++.h>
#define lli long long int
using namespace std;

char rnaa[302];

bool match(char a, char b)
{
  return ((a == 'F' && b == 'C') || (a == 'C' && b == 'F')) ||
         ((a == 'B' && b == 'S') || (a == 'S' && b == 'B'));
}

int main()
{
  while (scanf("%s", rnaa) != EOF && strcmp(rnaa, "Z"))
  {
    getchar();
    int ans = 0; stack<char> s;
    for (int i = 0; rnaa[i]; i ++)
    {
      if (!s.empty() && match(s.top(), rnaa[i]))
        s.pop(), ans ++;
      else
        s.push(rnaa[i]);
    }

    printf("%d\n", ans);
    memset(rnaa, '\0', sizeof(rnaa));
  }
  return(0);
}