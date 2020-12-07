#include <bits/stdc++.h>
using namespace std;

void swap(char *a, char *b)
{
  char aux = *a;
  *a = *b;
  *b = aux;
}

int main()
{
  int n; scanf("%d", &n);
  char s[n + 1], t[n + 1]; scanf("\n%s\n%s", s, t);

  vector<int> movements;
  for (int i = 0; i < n; i ++)
  {
    if (s[i] != t[i])
    {
      for (int j = i + 1; j < n; j ++)
        if (s[j] == t[i])
        {
          while (j > i)
          {
            swap(&s[j], &s[j - 1]);
            movements.push_back(j);
            j --;
          }
          break;
        }
    }

    if (s[i] != t[i])
    {
      printf("-1\n");
      return(0);
    }
  }

  printf("%d\n", (int) movements.size());
  for (int i = 0; i < movements.size(); i ++)
    printf("%d ", movements[i]);

  return(0);
}
