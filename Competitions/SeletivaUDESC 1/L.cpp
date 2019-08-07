#include <bits/stdc++.h>
using namespace std;

int fix(int a)
{
  a %= 11;
  return(a < 2 ? 0 : 11 - a);
}

int valid(string cpf, string last)
{
  int f = 0;
  for (int i = 0; i < 9; i ++)
    f += (cpf[i] - '0') * (10 - i);
  f = fix(f);
  if (last[0] - '0' != f) return(0);
  int l = 0;
  for (int i = 0; i < 9; i ++)
    l += (cpf[i] - '0') * (11 - i);
  l += 2 * f;
  l = fix(l);
  if (last[1] - '0' != l) return(0);
  return(1);
}

int main()
{
  int n; scanf("%d\n", &n);
  set<string> used;
  string cpf, last;
  for (int i = 0; i < n; i ++)
  {
    cin >> cpf >> last;
    if (last.size() == 1)
    {
      last += "0";
      reverse(last.begin(), last.end());
    }
    if (!valid(cpf, last))
      printf("Invalido\n");
    else
    {
      string res = cpf + last;
      if (used.count(res))
        printf("Clonado\n");
      else
      {
        printf("Sucesso\n");
        used.insert(res);
      }
    }
  }
  return(0);
}