#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

int main()
{
  int n, k; scanf("%d %d", &n, &k);
  string s; cin >> s;
  int letter[256]; memset(letter, 0, sizeof(letter));
  for (int i = 0; i < s.size(); i ++)
    letter[s[i]] ++;

  for (int i = 'a', algo = k; i <= 'z'; i ++)
  {
    if (letter[i] >= algo)
    {
      letter[i] -= algo;
      algo = 0;
    }
    else if (letter[i] < algo)
    {
      algo -= letter[i];
      letter[i] = 0;
    }
    DEBUG printf("%d %d\n", letter[i], algo);
  }

  string newS = "";
  for (int i = s.size() - 1; i >= 0; i --)
    if (letter[s[i]])
    {
      newS += s[i];
      letter[s[i]] --;
    }
  reverse(newS.begin(), newS.end());
  cout << newS << endl;

  return(0);
}