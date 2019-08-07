#include <bits/stdc++.h>
using namespace std;

void preProcess(string subString, int backTable[])
{
  for (int i = 0; subString[i]; i ++) backTable[i] = -1; backTable[subString.size()] = -1;
  int i = 0, j = -1;
  while (subString[i])
  {
    while (j >= 0 && subString[i] != subString[j])
      j = backTable[j];
    i ++; j ++;
    backTable[i] = j;
  }
}

int kmpSearch(string s, string subString, int backTable[])
{
  int i = 0, j = 0;
  while (s[i])
  {
    while (j >= 0 && s[i] != subString[j])
      j = backTable[j];
    i ++; j ++;
    if (!subString[j])
      return(1);
  }
  return(0);
}

int main()
{
  int t; scanf("%d", &t);
  while (t -- > 0)
  {
    string a, b, rev;
    cin >> a; getchar(); cin >> b;
    b += b;
    rev = b;
    while (b.size() < 2*a.size() + 1)
      b += rev;
    rev = b;
    reverse(rev.begin(), rev.end());
    //cout << a << ' ' << b << endl;

    int backTable[a.size() + 1], sub = 0;
    preProcess(a, backTable);
    if (kmpSearch(b, a, backTable) || kmpSearch(rev, a, backTable))
      printf("S\n");
    else
      printf("N\n");
  }
  return(0);
}