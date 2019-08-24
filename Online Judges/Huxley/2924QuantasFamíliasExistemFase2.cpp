#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n;
struct Person
{
  char name[100]; int age, sex;
  void print()
  {
    printf("Nome: %s\nIdade: %d\nSexo: %s\n", name, age, sex ? "Masculino" : "Feminino");
  }
};
Person people[maxN];
int parent[maxN];
bool visited[maxN];
vector<vector<int>> families;

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
    scanf(" %s %d %d", people[i].name, &people[i].age, &people[i].sex);
  for (int i = 0; i < n; i ++)
    scanf("%d", &parent[i]);

  for (int i = 0; i < n; i ++)
    if (!visited[i])
    {
      families.push_back(vector<int>());
      families.back().push_back(i), visited[i] = true;
      for (int at = parent[i]; at != i; at = parent[at])
        families.back().push_back(at), visited[at] = true;
    }

  printf("Quantidade de Familias: %d\n", (int) families.size());
  for (int i = 0; i < families.size(); i ++)
  {
    printf("\nFamília #%d: %d Pessoas\n", i + 1, (int) families[i].size());
    for (int j = 0; j < families[i].size(); j ++)
    {
      printf("\n");
      people[families[i][j]].print();
    }
    printf("\n####################\n");
  }

  return(0);
}