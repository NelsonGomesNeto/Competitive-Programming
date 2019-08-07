#include <bits/stdc++.h>
using namespace std;

int isPalindrome(char s[])
{
  int i, j;
  for (j = 0; s[j]; j ++); j --;
  for (i = 0; s[i]; i ++, j --)
    if (s[i] != s[j]) return(0);
  return(1);
}

void insert(char s[], char let, int at)
{
  char aux[1000]; strcpy(aux, s);
  for (int i = 0; i < at; i ++)
    s[i] = aux[i];
  s[at] = let;
  for (int i = at + 1; aux[i - 1]; i ++)
    s[i] = aux[i - 1];
}

int main()
{
  char s[1000];
  scanf("%s", s);

  char i; int j;

  for (i = 'a'; i <= 'z'; i ++)
  {
    for (j = 0; s[j]; j ++)
    {
      char aux[1000]; strcpy(aux, s);
      insert(s, i, j);
      if (isPalindrome(s))
      {
        printf("%s\n", s);
        return(0);
      }
      strcpy(s, aux);
    }
    char aux[1000]; strcpy(aux, s);
    insert(s, i, j);
    if (isPalindrome(s))
    {
      printf("%s\n", s);
      return(0);
    }
    strcpy(s, aux);
  }

  printf("NA\n");

  return(0);
}