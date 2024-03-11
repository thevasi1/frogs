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
    struct StackNode *stackNode = newNode(data);
    stackNode->next = *root;
    *root = stackNode;
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

canLeftJump(char *frogs, int frogIndex)
{
    int frontFrogIndex = frogIndex + 1;
    char frontFrog = frogs[frontFrogIndex];

    return frogs[frogIndex] == LEFT_FROG && frontFrog == EMPTY_SPACE;
}

canRightJump(char *frogs, int frogIndex)
{
    int behindFrogIndex = frogIndex - 1;
    char behindFrog = frogs[behindFrogIndex];

    return frogs[frogIndex] == RIGHT_FROG && behindFrog == EMPTY_SPACE;
}

int canJump(char *frogs, int frogIndex)
{
    return canLeftJump(frogs, frogIndex) || canRightJump(frogs, frogIndex);
}

canLeftDoubleJump(char *frogs, int frogIndex)
{
    int frontFrogIndex = frogIndex + 2;
    char frontFrog = frogs[frontFrogIndex];

    return frogs[frogIndex] == LEFT_FROG && frontFrog == EMPTY_SPACE;
}

canRightDoubleJump(char *frogs, int frogIndex)
{
    int behindFrogIndex = frogIndex - 2;
    char behindFrog = frogs[behindFrogIndex];

    return frogs[frogIndex] == RIGHT_FROG && behindFrog == EMPTY_SPACE;
}
int canDoubleJump(char *frogs, int frogIndex)
{
    return canLeftDoubleJump(frogs, frogIndex) || canRightDoubleJump(frogs, frogIndex);
}

void swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

void doJump(char *frogs, int frogIndex, int *emptyIndex)
{
    swap(&frogs[frogIndex], &frogs[*emptyIndex]);
    *emptyIndex = frogIndex;
}

void rec(struct StackNode** root, char *frogs, int *emptyIndex)
{
    if (strcmp(frogs, "111_000")){
        return;
    }

    if(canLeftJump)
    {
        doJump();
        push();
        rec();
        pop()
    }
    if(canRightJump)
    {
        doJump();
        push();
        rec();
        pop()
    }
    if(canLeftDoubleJump)
    {
        doJump();
        push();
        rec();
        pop()
    }
    if(canRightDoubleJump)
    {
        doJump();
        push();
        rec();
        pop()
    }

    pop();
}

int main()
{
    struct StackNode* root = NULL;
    int frogsTeam = 3;
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

    rec(root, frogs, emptyIndex);
    while(top(root) != NULL) {
        pop(root);
    }

    return 0;
}
