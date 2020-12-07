#include <bits/stdc++.h>
using namespace std;

string keyboard[3] = {"qwertyuiop", "asdfghjkl;", "zxcvbnm,./"};

int main()
{
  char dir; string s;
  scanf("%c\n", &dir);
  cin >> s;

  char sub[255][2]; int j;
  for (int i = 0; i < 3; i ++)
  {
    for (j = 0; keyboard[i][j + 1]; j ++)
    {
      sub[keyboard[i][j]][1] = keyboard[i][j + 1];
      if (j)
        sub[keyboard[i][j]][0] = keyboard[i][j - 1];
    }
    sub[keyboard[i][j]][0] = keyboard[i][j - 1];
  }

  for (int i = 0; s[i]; i ++)
    if (dir == 'R')
      s[i] = sub[s[i]][0];
    else
      s[i] = sub[s[i]][1];

  cout << s << endl;

  return(0);
}