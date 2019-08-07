#include<stdio.h>
#include<stdlib.h>

typedef unsigned char BYTE;
typedef struct _tree Tree;
typedef struct priority_q priority_queue;

Tree* build_huffman_tree(int *array);
void creat_table(BYTE tabela[][200], Tree* bt, BYTE *string, int position);
void print_tree(Tree *bt);

int main()
{
    int array[256];
    BYTE string[200], a, table[256][200];
    int k;
    for(k = 0; k < 256; k++)
        array[k] = 0;
    for(k = 0; k < 256; k++)
        table[k][0] = '\0';

    while(scanf("%c", &a) != EOF)
    {
        array[a]++;
    }
    Tree *huff = build_huffman_tree(array);
    printf("Tree	-	");
    print_tree(huff);
    printf("\n");
    creat_table(table, huff, string, 0);
    for(k = 0; k < 256; k++)
    {
        if(table[k][0] != '\0')
            printf("%c	-	%s\n", k, table[k]);
    }

    return 0;
}
struct priority_q{
    Tree *head;
};

struct _tree{
    int frequency;
    BYTE character;
    Tree *next;
    Tree *left;
    Tree *right;
};
Tree* creat_node(BYTE character, int frequencia){

    Tree *new_node = (Tree*) malloc(sizeof(Tree));
    new_node->character= character;
    new_node->frequency = frequencia;
    new_node->next = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}
Tree* dequeue(priority_queue *pq){

    if(pq->head == NULL)
        return NULL;
    Tree *aux = pq->head;
    pq->head = pq->head->next
;    aux->next = NULL;
    return aux;
}

priority_queue* creat_priority_queue(){

    priority_queue *new_pq = (priority_queue*) malloc(sizeof(priority_queue));
    new_pq->head = NULL;
    return new_pq;

}

void enqueue(Tree *new_node, priority_queue *pq){

    if(pq->head == NULL || pq->head->frequency > new_node->frequency){
        new_node->next = pq->head;
        pq->head = new_node;
        return ;
    }
    if(new_node->frequency == pq->head->frequency)
    {
        if(new_node->character < pq->head->character)
        {
            new_node->next = pq->head;
            pq->head = new_node;
            return;
        }
        else
        {
            new_node->next = pq->head->next;
            pq->head->next = new_node;
            return;
        }

    }

    Tree *aux = pq->head;
    while(aux->next != NULL && aux->next->frequency < new_node->frequency)
        aux = aux->next;

    new_node->next = aux->next;
    aux->next = new_node;
    return ;
}
Tree* build_Tree(priority_queue *pq){

    Tree *aux;

    while(1){

        aux = creat_node('*', 0);
        aux->left = dequeue(pq);

        if(aux->left != NULL)
            aux->frequency += aux->left->frequency;

        aux->right = dequeue(pq);
        if(aux->right != NULL)
            aux->frequency += aux->right->frequency;

        if(pq->head == NULL)
            break;

        enqueue(aux, pq);

    }
    return aux;
}


Tree* build_huffman_tree(int *array){

    priority_queue *pq = creat_priority_queue();
    Tree *huffman_tree;

    int i;

    for(i = 255; i >= 0; i--){
        if(*(array+i) != 0)
            enqueue(creat_node(i, *(array+i)), pq);
    }

    huffman_tree = build_Tree(pq);

    return  (Tree*)huffman_tree;
}
void creat_table(BYTE tabela[][200], Tree* bt, BYTE *string, int position){

    if(bt->left == NULL && bt->right == NULL){
        string[position] = '\0';
        strncpy(tabela[bt->character],string,position+1);
        return;
    }
    if(bt->left != NULL)
    {
        string[position] = '0';
        creat_table(tabela,bt->left, string, position+1);
    }
    if(bt->right != NULL)
    {
        string[position] = '1';
        creat_table(tabela,bt->right, string, position+1);
    }
}

void print_tree(Tree *bt)
{
    if(bt == NULL)
    {
        return ;
    }
    print_tree(bt->left);
    printf("%c", bt->character);
    print_tree(bt->right);
}
