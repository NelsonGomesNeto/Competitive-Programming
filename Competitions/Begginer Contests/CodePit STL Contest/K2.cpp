#include <bits/stdc++.h>
using namespace std;

int main()
{
  char word[70];
  while (scanf("%[^\n]", word) && word[0] != '#')
  {
    if (next_permutation(word, word + strlen(word)))
    {
      printf("%s\n", word);
    }
    else
    {
      printf("No Successor\n");
    }
    getchar();
  }
  return 0;
}
