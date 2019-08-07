#include <bits/stdc++.h>

int main()
{
  char s[(int) 1e5 + 1]; scanf("%s", s);
  int hats[2]; memset(hats, 0, sizeof(hats));
  for (int i = 0; s[i]; i ++) hats[s[i] - '0'] ++;
  if (!(hats[1] & 1)) printf("Yes\n");
  else printf("No\n");
  return(0);
}
