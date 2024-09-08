#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  for all letters: cnt[letter] % k == 0
*/

const int maxN = 1e5;
int n, k;
char s[maxN + 1];
int cnt[256];

int getToAdd(int count)
{
  return (k - count % k) % k;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &k);
    scanf(" %s", s);

    if (n % k != 0)
    {
      printf("-1\n");
      continue;
    }

    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++)
      cnt[s[i]]++;

    int sum = 0;
    for (char letter = 'a'; letter <= 'z'; letter++)
      sum += getToAdd(cnt[letter]);

    // ans == s won't make it
    if (sum != 0)
    {
      bool found = false;
      // Find the first position where I need to make ans > s
      for (int i = n - 1; i >= 0 && !found; i--)
      {
        for (char letter = s[i] + 1; letter <= 'z'; letter++)
        {
          // Update sum and cnt
          sum -= getToAdd(cnt[s[i]]);
          sum -= getToAdd(cnt[letter]);
          cnt[s[i]]--;
          cnt[letter]++;
          sum += getToAdd(cnt[s[i]]);
          sum += getToAdd(cnt[letter]);

          // Found a valid change
          if (sum <= n - (i + 1))
          {
            // Update s
            s[i] = letter;
            for (int j = i + 1; j < n; j++)
            {
              while (j < n && sum < n - j)
              {
                sum -= getToAdd(cnt['a']);
                s[j++] = 'a';
                cnt['a']++;
                sum += getToAdd(cnt['a']);
              }
              if (j == n) break;

              char bestLetter = 'a';
              while (bestLetter <= 'z' && getToAdd(cnt[bestLetter]) == 0) bestLetter++;
              if (bestLetter > 'z') bestLetter = 'a';

              sum -= getToAdd(cnt[bestLetter]);
              s[j] = bestLetter;
              cnt[bestLetter]++;
              sum += getToAdd(cnt[bestLetter]);
            }
            found = true;
            break;
          }

          sum -= getToAdd(cnt[s[i]]);
          sum -= getToAdd(cnt[letter]);
          cnt[s[i]]++;
          cnt[letter]--;
          sum += getToAdd(cnt[s[i]]);
          sum += getToAdd(cnt[letter]);
        }

        sum -= getToAdd(cnt[s[i]]);
        cnt[s[i]]--;
        sum += getToAdd(cnt[s[i]]);
      }
    }

    printf("%s\n", s);
  }
  return 0;
}
