#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char EMPTY_SPACE = '_';
const char LEFT_FROG = '0';
const char RIGHT_FROG = '1';

struct StackNode
{
    char *data;
    struct StackNode *next;
};

struct StackNode *newNode(char *data)
{
    struct StackNode *stackNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

int isEmpty(struct StackNode *root)
{
    return !root;
}

void push(struct StackNode **root, char *data)
{
    printf("\n we work with %d\n", root);
    printf("we point at %d\n", (*root)->next);
    struct StackNode *stackNode = newNode(data);
    stackNode->next = *root;
    printf("we will point from %d\n", stackNode);
    printf("\nfrogs before push are: %s \n", (*root)->data);
    *root = stackNode;
    printf("\nfrogs after push are: %s \n", (*root)->data);
    printf("%s pushed to stack\n", data);
}

char *pop(struct StackNode **root)
{
    if (isEmpty(*root))
    {
        return NULL;
    }

    struct StackNode *temp = *root;
    *root = (*root)->next;
    char *popped = temp->data;
    free(temp);

    printf("%s popped from stack\n", popped);
    return popped;
}

char *top(struct StackNode *root)
{
    if (isEmpty(root))
    {
        return NULL;
    }
    printf("Top element is %s\n", root->data);
    return root->data;
}

int canLeftJump(char *frogs, int frogIndex)
{
    int frontFrogIndex = frogIndex + 1;
    char frontFrog = frogs[frontFrogIndex];

    return frogs[frogIndex] == LEFT_FROG && frontFrog == EMPTY_SPACE;
}

int canRightJump(char *frogs, int frogIndex)
{
    int behindFrogIndex = frogIndex - 1;
    char behindFrog = frogs[behindFrogIndex];

    return frogs[frogIndex] == RIGHT_FROG && behindFrog == EMPTY_SPACE;
}

int canLeftDoubleJump(char *frogs, int frogIndex)
{
    int frontFrogIndex = frogIndex + 2;
    char frontFrog = frogs[frontFrogIndex];

    return frogs[frogIndex] == LEFT_FROG && frontFrog == EMPTY_SPACE;
}

int canRightDoubleJump(char *frogs, int frogIndex)
{
    int behindFrogIndex = frogIndex - 2;
    char behindFrog = frogs[behindFrogIndex];

    return frogs[frogIndex] == RIGHT_FROG && behindFrog == EMPTY_SPACE;
}

void doJump(char *frogs, int frogIndex, int *emptyIndex)
{
    swap(&frogs[frogIndex], &frogs[*emptyIndex]);
    *emptyIndex = frogIndex;
}

void swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

void rec(struct StackNode** root, char *frogs, int *emptyIndex)
{
    top(*root);
    if (!strcmp(frogs, "11_00")){
        return;
    }
    if(canLeftJump(frogs, *emptyIndex - 1))
    {
        doJump(frogs, *emptyIndex - 1, emptyIndex);
        printf("\nfrogs: %s\n", frogs);
        
    printf("\n we are seinding %d %d %d\n", root, *root, &root);
        push(&root, frogs);
        rec(&root, frogs, emptyIndex);
        pop(&root);
    }
    // if(canRightJump(frogs, *emptyIndex + 1))
    // {
    //     doJump(frogs, *emptyIndex + 1, emptyIndex);
    //     push(&root, *frogs);
    //     rec(&root, frogs, emptyIndex);
    //     pop(&root);
    // }
    // if(canLeftDoubleJump(frogs, *emptyIndex - 2))
    // {
    //     doJump(frogs, *emptyIndex - 2, emptyIndex);
    //     push(&root, *frogs);
    //     rec(&root, frogs, emptyIndex);
    //     pop(&root);
    // }
    // if(canRightDoubleJump(frogs, *emptyIndex + 2))
    // {
    //     doJump(frogs, *emptyIndex + 2, emptyIndex);
    //     push(&root, *frogs);
    //     rec(&root, frogs, emptyIndex);
    //     pop(&root);
    // }

    return;
}

int main()
{
    struct StackNode* root = NULL;
    int frogsTeam = 2;
    // scanf("%d", &frogsTeam);
    printf("num of frogs: %d\n", frogsTeam);

    char frogs[frogsTeam * 2 + 1];
    for (int i = 0; i < frogsTeam; ++i)
    {
        frogs[i] = LEFT_FROG;
    }
    frogs[frogsTeam] = '_';
    for (int i = frogsTeam + 1; i < frogsTeam * 2 + 1; ++i)
    {
        frogs[i] = RIGHT_FROG;
    }
    frogs[frogsTeam * 2 + 1] = '\0';

    // printf("frogs 1 : %s\n", frogs);
    int emptyIndex = frogsTeam;


    printf("\n iniital %d %d\n", root, &root);
    rec(&root, frogs, &emptyIndex);
    while(top(root) != NULL) {
        pop(root);
    }

    return 0;
}
