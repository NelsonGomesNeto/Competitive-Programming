#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5 + 1; int n;
char ss[maxN + 1];
string key;
string message;

char cypher[256][256];
string vowels = "aeiou";

int main()
{
  DEBUG {
    printf("   "); for (int j = 'a'; j <= 'z'; j++) printf(" %c", j);
    printf("\n");
  }
  for (int i = 'a'; i <= 'z'; i++)
  {
    DEBUG printf("%c -", i);
    for (int j = 'a', shift = i - 'a'; j <= 'z'; j++)
    {
      cypher[i][j] = (('a' + shift + j - 'a') - 'a') % 26 + 'a';
      DEBUG printf(" %c", cypher[i][j]);
    }
    DEBUG printf("\n");
  }

  while (~scanf(" %s", ss))
  {
    key = string(ss);
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
      scanf(" %[^\n]", ss);
      message = string(ss);
      bool waiting = true;
      int j = 0;
      for (int i = 0; i < message.size(); i++)
      {
        while (i < message.size() && message[i] == ' ') i++;

        if (i == message.size()) break;

        bool consonant = true;
        for (char c: vowels)
          if (message[i] == c)
            consonant = false;

        while (i < message.size() && message[i] >= 'a' && message[i] <= 'z')
        {
          if (consonant) message[i] = cypher[key[j]][message[i]];
          i++;
          if (consonant) j = (j + 1) % key.size();
        }
      }
      printf("%s\n", message.c_str());
      DEBUG printf("\t%s - %s\n", key.c_str(), message.c_str());
    }
  }
  return 0;
}