#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n, p;
struct Person
{
  char name[100];
  int sex, left, right;
  int descendants;
  void read() { scanf(" %s %d %d %d", name, &sex, &left, &right); }
  void print() { printf("%s: %s\nQuantidade de Decendentes: %d\n", sex ? "Patriarca" : "Matriarca", name, descendants); }
};
Person people[maxN];
int roots[maxN];

int dfs(int u)
{
  if (u == -1) return -1;
  people[u].descendants += dfs(people[u].left) + dfs(people[u].right) + 2;
  return people[u].descendants;
}

int main()
{
  scanf("%d %d", &n, &p);
  for (int i = 0; i < n; i ++)
    people[i].read();
  for (int i = 0; i < p; i ++)
  {
    scanf("%d", &roots[i]);
    dfs(roots[i]);
  }
  for (int i = 0; i < p; i ++)
  {
    people[roots[i]].print();
    if (i < p - 1) printf("\n");
  }

  return(0);
}