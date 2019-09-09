#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n, m;
int s[maxN], ds[maxN], t[maxN], dt[maxN];
int noteMap[256];

int fix(int i, int sz)
{
  return ((i % sz) + sz) % sz;
}
void read(int song[], int dsong[], int sz)
{
  char note[3];
  for (int i = 0; i < sz; i ++)
  {
    scanf(" %s", note);
    song[i] = fix(noteMap[note[0]] + (note[1] == '#') - (note[1] == 'b'), 12);
    if (i) dsong[i - 1] = fix(song[i] - song[i - 1], 12);
  }
}
void print(int song[], int dsong[], int sz)
{
  for (int i = 0; i < sz; i ++)
    printf("%d%c", song[i], i < sz - 1 ? ' ' : '\n');
  printf("\t");
  for (int i = 0; i < sz - 1; i ++)
    printf("%d%c", dsong[i], i < sz - 2 ? ' ' : '\n');
}

int backTable[maxN + 1];

void preProcess(int subStr[], int subStrSize)
{
  memset(backTable, -1, sizeof(backTable));
  for (int i = 0, j = -1; i < subStrSize;)
  {
    while (j >= 0 && subStr[i] != subStr[j]) j = backTable[j];
    i ++, j ++;
    backTable[i] = j;
  }
}
vector<int> kmpSearch(int str[], int strSize, int subStr[], int subStrSize)
{
  vector<int> occurrences;
  for (int i = 0, j = 0; i < strSize;)
  {
    while (j >= 0 && str[i] != subStr[j]) j = backTable[j];
    i ++, j ++;
    if (j == subStrSize)
    {
      occurrences.push_back(i - j);
      j = backTable[j];
    }
  }
  return occurrences;
}

int main()
{
  noteMap['C'] = 0, noteMap['D'] = 2, noteMap['E'] = 4;
  noteMap['F'] = 5, noteMap['G'] = 7, noteMap['A'] = 9;
  noteMap['B'] = 11;
  // b will subtract 1 and # will add 1 (remember to use mod 12)
  // This way we make sure that B# to c, Fb to E and all that ;)

  while (scanf("%d %d", &n, &m) && n + m)
  {
    read(s, ds, n); read(t, dt, m);

    // print(s, ds, n);
    // print(t, dt, m);

    preProcess(dt, m - 1);
    vector<int> occurrences = kmpSearch(ds, n - 1, dt, m - 1);
    printf("%c\n", occurrences.empty() ? 'N' : 'S');
  }

  return(0);
}