#include <stdio.h>
#include <stdlib.h>
#define lista struct lista

lista
{
  int item;
  lista *next;
};

lista* create_linked_list()
{
  return(NULL);
}

lista* add(lista *head, int item)
{
  lista *novo = (lista*) malloc(sizeof(lista));
  novo->item = item;
  novo->next = head;
  return(novo);
}

lista* search(lista *head, int item)
{
  while (head != NULL)
  {
    if (head->item == item)
    {
      return(head);
    }
    head = head->next;
  }
  return(NULL);
}

lista* remov(lista *head, int item)
{
  lista *previous = NULL;
  lista *current = head;
  while (current != NULL && current->item != item)
  {
    previous = current;
    current = current->next;
  }
  if (current == NULL)
  {
    return(head);
  }
  if (previous == NULL)
  {
    head = current->next;
  }
  else
  {
    previous->next = current->next;
  }
  free(current);
  return(head);
}

int main()
{
  int tamA, i, valor; scanf("%d", &tamA);
  lista *A = create_linked_list();
  for (i = 0; i < tamA; i ++)
  {
    scanf("%d", &valor);
    A = add(A, valor);
  }

  int tamB; scanf("%d", &tamB);
  lista *B = create_linked_list();
  for (i = 0; i < tamB; i ++)
  {
    scanf("%d", &valor);
    B = add(B, valor);
  }

  for (i = 0; i < tamB; i ++)
  {
    //printf("%d\n", B->item);
    if (search(A, B->item) == NULL)
    {
      printf("0\n");
      return(0);
    }
    B = B->next;
  }
  printf("1\n");
  return(0);
}
