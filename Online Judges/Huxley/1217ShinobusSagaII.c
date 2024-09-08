#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tree tree_t;

struct tree
{
  char value;
  tree_t *left, *right;
};

tree_t* createTree(char value, tree_t *left, tree_t *right)
{
  tree_t* temp = (tree_t*) malloc(1 * sizeof(tree_t));
  temp->value = value;
  temp->left = left;
  temp->right = right;
  return(temp);
}

void setNode(tree_t *tree, char value)
{
  tree->value = value;
}

void printPreOrderWithLevels(tree_t *tree, int levels)
{
  if (tree != NULL)
  {
    int i;
    for (i = 0; i < levels; i ++)
      printf(" ");
    printf("%c\n", tree->value);
    printPreOrderWithLevels(tree->left, levels + 1);
    printPreOrderWithLevels(tree->right, levels + 1);
  }
}

void printInOrder(tree_t *tree)
{
  if (tree != NULL)
  {
    printInOrder(tree->left);
    if (tree->value != '*')
      printf("%c", tree->value);
    printInOrder(tree->right);
  }
}

void printPosOrder(tree_t *tree)
{
  if (tree != NULL)
  {
    printPosOrder(tree->left);
    printPosOrder(tree->right);
    if (tree->value != '*')
      printf("%c", tree->value);
  }
}

tree_t* createTreeFromScan(tree_t **tree, int *i, char *preFix)
{
  if (*tree == NULL)
    *tree = createTree('*', NULL, NULL);
  char value = preFix[*i]; int pos = 0;
  (*i) += 1;
  //tree_t *stack[1001];
  if (value != '*')
  {
    //tree_t *left, *right;
    //left = pos >= 0 ? stack[pos --] : NULL;
    //right = pos >= 0 ? stack[pos --] : NULL;
    //stack[++ pos] = createTree(value, right, left);
    *tree = createTree(value, createTreeFromScan(&(*tree)->left, &(*i), preFix), createTreeFromScan(&(*tree)->right, &(*i), preFix));
  }
  else
  {
    //tree_t *leaf = createTree(value, NULL, NULL);
    //stack[++ pos] = leaf;
    *tree = createTree(value, NULL, NULL);
  }
  return(*tree);
}


int main()
{
  tree_t *tree = NULL;
  char postFix[1001], preFix[1001]; scanf("%[^\n]", postFix);
  int i, j = strlen(postFix);
  for (i = 0, j = strlen(postFix) - 1; postFix[i] != '\0'; i ++, j --)
    preFix[i] = postFix[j];
  j = 0;
  preFix[i] = '\0';
  tree = createTreeFromScan(&tree, &j, preFix);
  printf("Mensagem decodificada: "); printInOrder(tree); printf("\n");
  printf("Arvore construida:\n");
  printPreOrderWithLevels(tree, 0);
  return(0);
}