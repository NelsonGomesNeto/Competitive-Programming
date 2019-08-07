#include <bits/stdc++.h>
using namespace std;

set<string> differentEmails;

int main()
{
  int n; scanf("%d\n", &n);
  for (int i = 0; i < n; i ++)
  {
    string email;
    char a; bool plus = false;
    while (scanf("%c", &a) && a != '@')
    {
      if (a == '+') { plus = true; break; }
      if (a != '.') email.push_back(a);
    }
    if (plus) while (scanf("%c", &a) && a != '@');
    plus = false;
    email.push_back('@');
    while (scanf("%c", &a) && a != '\n')
    {
      // if (a == '+') { plus = true; break; }
      // if (a != '.') 
      email.push_back(a);
    }
    if (plus) while (scanf("%c", &a) && a != '\n');
    differentEmails.insert(email);
  }
  printf("%d\n", (int) differentEmails.size());
  return(0);
}