#include <bits/stdc++.h>
char vowel[7] = "aeiouy";

int isVowel(char a)
{
  for (int k = 0; k < 6; k ++) if (tolower(a) == vowel[k]) return(1);
  return(0);
}

int main()
{
  char a;
  while (scanf("%c", &a) && a != '\n')
  {
    if (isVowel(a)) continue;
    printf(".%c", tolower(a));
  }
  printf("\n");
}