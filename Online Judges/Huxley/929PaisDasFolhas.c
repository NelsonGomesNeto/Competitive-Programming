#include <stdio.h>
#define maxN 10000

int n;
typedef struct Tree Tree;
struct Tree
{
  int left, right;
};
Tree tree[maxN];
int parents[maxN], pp;

int isLeaf(int u)
{
  if (u == -1) return(0);
  if (tree[u].left == -1 && tree[u].right == -1) return(1);
  int leftIsLeaf = isLeaf(tree[u].left);
  int rightIsLeaf = isLeaf(tree[u].right);
  if (leftIsLeaf || rightIsLeaf) parents[pp ++] = u;
  return(0);
}

void swap(int *a, int *b) { int aux = *a; *a = *b; *b = aux; }
void sort(int array[], int size)
{
  int i, j;
  for (i = 0; i < size - 1; i ++)
    for (j = i + 1; j < size; j ++)
      if (array[i] > array[j])
        swap(&array[i], &array[j]);
}

int main()
{
  scanf("%d", &n);
  int i;
  for (i = 0; i < n; i ++) scanf("%d %d", &tree[i].left, &tree[i].right);

  if (isLeaf(0)) parents[pp ++] = 0;
  sort(parents, pp);
  for (i = 0; i < pp; i ++)
    printf("%d\n", parents[i]);

  return(0);
}