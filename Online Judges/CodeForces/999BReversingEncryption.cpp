#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

void encrypt(string& s, int n)
{
  reverse(s.begin(), s.end());
  DEBUG cout << s << endl;
  for (int i = 2; i < n; i ++)
    if (n % i == 0)
    {
      reverse(s.end()-i, s.end());
      DEBUG cout << s << endl;
    }
}

int main()
{
  int n; scanf("%d", &n);
  string s; cin >> s;
  encrypt(s, n);
  cout << s << endl;
  return(0);
}