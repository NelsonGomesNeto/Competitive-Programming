#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
char ss[maxN + 1];
string s;

struct Term
{
  int c = 0, e = 0;
  void print(char end = '\n')
  {
    if (c == -1 && e != 0) printf("-");
    else if (c == 1 && e != 0);
    else printf("%d", c);

    if (e != 0) printf("x");

    if (e < 0 || e > 1)
      printf("^%d", e);

    if (end != '\0') printf("%c", end);
  }
  void derivate()
  {
    c *= e;
    e--;
  }
};
map<int, Term> terms;

bool isDigit(char c)
{
  return c >= '0' && c <= '9';
}
int digit(char c)
{
  return c - '0';
}
int readNum(int &i)
{
  int num = 0;
  while (i < s.size() && isDigit(s[i]))
  {
    num = num * 10 + digit(s[i]);
    i++;
  }
  return num;
}
Term readTerm(int &i)
{
  Term t = Term{0, 0};

  if (s[i] == 'x')
  {
    t = Term{1, 1};
    i++;
  }
  else if (s[i] == '-')
  {
    i++;
    if (s[i] == 'x')
    {
      t = Term{-1, 1};
      i++;
    }
    else t.c = -readNum(i);
  }
  else
  {
    t.c = readNum(i);
  }

  if (i < s.size() && s[i] == 'x')
  {
    t.e = 1;
    i++;
  }

  if (i < s.size() && s[i] == '^')
  {
    i++;
    if (s[i] == '-')
    {
      i++;
      t.e = -readNum(i);
    }
    else
    {
      t.e = readNum(i);
    }
  }

  return t;
}

int main()
{
  while (~scanf(" %s", ss))
  {
    terms.clear();

    s = string(ss);

    for (int i = 0; i < s.size();)
    {
      DEBUG printf("\t%s\n", s.substr(i).c_str());
      bool neg = false;
      if (i != 0)
      {
        while (i < s.size() && (s[i] == '+' || s[i] == '-'))
        {
          if (s[i] == '-') neg = !neg;
          i++;
        }
      }

      Term t = readTerm(i);
      if (neg) t.c *= -1;

      DEBUG t.print();
      if (!terms.count(t.e)) terms[t.e] = t;
      else terms[t.e].c += t.c;
    }

    bool first = true;
    for (auto &it: terms)
    {
      it.second.derivate();
      if (it.second.c != 0)
      {
        if (!first && it.second.c > 0)
          printf("+");

        it.second.print('\0');
        first = false;
      }
    }
    if (first) printf("0");

    printf("\n");

    DEBUG printf("------\n");
  }
  return 0;
}