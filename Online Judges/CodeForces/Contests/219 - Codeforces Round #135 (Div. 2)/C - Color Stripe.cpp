#include <bits/stdc++.h>
using namespace std;

int n, k;

int main()
{
  scanf("%d %d", &n, &k);
  char s[n + 1]; scanf(" %s", s);

  int sm = 0;
  if (k == 2)
  {
    int a = 0, b = 0, turn = 0;
    for (int i = 0; i < n; i ++, turn = 1 - turn)
      if ((s[i] == 'A' && turn) || (s[i] == 'B' && !turn)) a ++;
      else b ++;
    if (a < b) turn = 0;
    else turn = 1;
    for (int i = 0; i < n; i ++, turn = 1 - turn)
      if (s[i] == 'A' && turn)
        s[i] = 'B', sm ++;
      else if (s[i] == 'B' && !turn)
        s[i] = 'A', sm ++;
  }
  else
  {
    for (int i = 0, end; i < n - 1; i ++)
      if (s[i] == s[i + 1])
      {
        end = i + 1; while (end < n && s[i] == s[end]) end ++;
        end --;
        int size = end - i + 1, letter = s[i] == 'A' ? 'B' : 'A';
        if (size & 1) for (int j = i + 1; j <= end; j += 2) s[j] = letter, sm ++;
        else if (size > 2) for (int j = i + 1; j < end; j += 2) s[j] = letter, sm ++;
        i = end - 1;
      }
    for (int i = 1; i < n; i ++)
      if (s[i - 1] == s[i])
      {
        if (i == n - 1) s[i] = s[i] == 'A' ? 'B' : 'A';
        else for (char j = 'A'; j <= 'Z'; j ++) if (j != s[i] && j != s[i + 1]) { s[i] = j; break; }
        sm ++;
      }
  }
  

  printf("%d\n%s\n", sm, s);
  return(0);
}