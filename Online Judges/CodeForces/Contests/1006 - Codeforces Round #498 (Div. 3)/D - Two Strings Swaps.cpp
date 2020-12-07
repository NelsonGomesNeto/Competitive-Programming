#include <bits/stdc++.h>
using namespace std;
#define DEBUG if(0)

int main()
{
  int n; scanf("%d", &n);
  int mid = n / 2;
  char aa[n + 1] = "", bb[n + 1] = "";
  scanf("\n%s\n%s", aa, bb);

  int ans = 0;
  for (int i = 0; i < mid; i ++)
  {
    char a = aa[i], b = aa[n - i - 1], c = bb[i], d = bb[n - i - 1];
    DEBUG printf("%c %c %c %c %d\n", a, b, c, d, ans);
    if ((a == b && b == c && c == d) || (a == b && c == d) || (a == c && b == d) || (a == d && b == c)) continue;
    else if ((a != b && a != c && a != d && b != c && b != d && c != d) || (a == b && b != c && b != d && c != d)) ans += 2;
    else ans ++;
  }
  if ((n & 1) && aa[mid] != bb[mid]) ans ++;

  printf("%d\n", ans);

  return(0);
}
// if ((a == b && b == c && c == d) || (a == b && c == d) || (a == c && b == d) || (a == d && b == c)) continue;
// else if ((a != b && b != c && c != d && a != c && b != d && a != d) || (a == b && b != c && b != d && c != d) || (a == c && a != b && a != d && b != d) || (a == d && a != b && a != c && b != c) || (b == c && b != a && b != d && a != d) || (c == d && c != a && c != b && a != b)) ans += 2;
// else ans ++;

// char lol[5] = {a, b, c, d, '\0'}; sort(lol, lol+5);
// a = lol[1]; b = lol[2]; c = lol[3]; d = lol[4];
// if (a == b && c == d) continue;
// else if ((a != b && b != c && c != d)) ans += 2;
// else ans ++;