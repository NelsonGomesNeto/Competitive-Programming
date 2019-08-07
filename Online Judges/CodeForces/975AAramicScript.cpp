#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  set<string> obj;
  char s[1001];
  for (int i = 0; i < n; i ++)
  {
    scanf(" %s", s);
    int letters[35]; memset(letters, 0, sizeof(letters));
    for (int j = 0; s[j]; j ++)
      letters[s[j] - 'a'] = 1;
    char o[35], k = 0;
    for (int j = 0; j < 35; j ++)
      if (letters[j])
        o[k ++] = j + 'a';
    o[k] = '\0';
    obj.insert(o);
  }

  printf("%d\n", (int) obj.size());

  return(0);
}