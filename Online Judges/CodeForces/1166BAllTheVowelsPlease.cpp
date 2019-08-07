#include <bits/stdc++.h>
using namespace std;

char vowels[6] = "aeiou";

int main()
{
  int k; scanf("%d", &k);

  bool can = false; int n, m;
  for (int i = 1, end = sqrt(k); !can && i <= end; i ++)
    if (k % i == 0 && k / i >= 5 && i >= 5)
      can = true, n = i, m = k / i;

  if (!can) printf("-1\n");
  else
  {
    char s[n][m + 1], ss[n*m + 1]; memset(s, '\0', sizeof(s)); memset(ss, '\0', sizeof(ss));
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++)
        s[i][j] = vowels[(j + i) % 5];
    for (int i = 0; i < n; i ++) for (int j = 0; j < m; j ++) ss[i*m + j] = s[i][j];
    printf("%s\n", ss);
    // for (int i = 0; i < n; i ++) printf("%s\n", s[i]);
  }

  return(0);
}
