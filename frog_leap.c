#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY_SPACE '_'
#define LEFT_FROG '0'
#define RIGHT_FROG '1'

struct StackNode
{
    char *data;
    struct StackNode *next;
};

struct StackNode *newNode(char *data)
{
    struct StackNode *stackNode = (struct StackNode *)malloc(sizeof(struct StackNode));

    int charSize = strlen(data);
    char *newData;

    newData = (char *)malloc(charSize * sizeof(char));
    strcpy(newData, data);

    stackNode->data = newData;
    stackNode->next = NULL;
    
    return stackNode;
}

void push(struct StackNode **root, char *data)
{
    struct StackNode *stackNode = newNode(data);
    stackNode->next = *root;
    *root = stackNode;
}

int isEmpty(struct StackNode *root)
{
    return !root;
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
    return popped;
}

char *top(struct StackNode *root)
{
    if (isEmpty(root))
    {
        return NULL;
    }
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

void rec(struct StackNode** root, char *frogs, int emptyIndex, char *winCondition)
{
    if (!strcmp(top(*root), winCondition)){
        return;
    }

    if(canLeftJump(top(*root), emptyIndex - 1))
    {
        strcpy(frogs, top(*root));
        doJump(frogs, emptyIndex - 1, &emptyIndex);
        push(root, frogs);
        rec(root, frogs, emptyIndex, winCondition);

    if (!strcmp(top(*root), winCondition)){
        return;
    }

        pop(root);
        ++emptyIndex;
    }
    if(canRightJump(top(*root), emptyIndex + 1))
    {
        strcpy(frogs, top(*root));
        doJump(frogs, emptyIndex + 1, &emptyIndex);
        push(root, frogs);
        rec(root, frogs, emptyIndex, winCondition);

    if (!strcmp(top(*root), winCondition)){
        return;
    }
        pop(root);
        --emptyIndex;
    }
    if(canLeftDoubleJump(top(*root), emptyIndex - 2))
    {
        strcpy(frogs, top(*root));
        doJump(frogs, emptyIndex - 2, &emptyIndex);
        push(root, frogs);
        rec(root, frogs, emptyIndex, winCondition);

    if (!strcmp(top(*root), winCondition)){
        return;
    }
        pop(root);
        emptyIndex+=2;
    }
    if(canRightDoubleJump(top(*root), emptyIndex + 2))
    {
        strcpy(frogs, top(*root));
        doJump(frogs, emptyIndex + 2, &emptyIndex);
        push(root, frogs);
        rec(root, frogs, emptyIndex, winCondition);

    if (!strcmp(top(*root), winCondition)){
        return;
    }
        pop(root);
        emptyIndex-=2;
    }
}

int main()
{
    struct StackNode* root = NULL;
    int frogsTeam;

    scanf("%d", &frogsTeam);
    int emptyIndex = frogsTeam;

    char frogs[frogsTeam * 2 + 1];
    char winCondition[frogsTeam * 2 + 1];

    for (int i = 0; i < frogsTeam; ++i)
    {
        frogs[i] = LEFT_FROG;
        winCondition[i] = RIGHT_FROG;
    }

    frogs[frogsTeam] = '_';
    winCondition[frogsTeam] = '_';

    for (int i = frogsTeam + 1; i < frogsTeam * 2 + 1; ++i)
    {
        frogs[i] = RIGHT_FROG;
        winCondition[i] = LEFT_FROG;
    }

    frogs[frogsTeam * 2 + 1] = '\0';
    winCondition[frogsTeam * 2 + 1] = '\0';

    push(&root, frogs);
    rec(&root, frogs, emptyIndex, winCondition);

    while(top(root) != NULL) {
        printf("%s\n", top(root));
        pop(&root);
    }

    return 0;
}
