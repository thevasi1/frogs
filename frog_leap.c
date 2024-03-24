#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY_SPACE '_'
#define LEFT_FROG '>'
#define RIGHT_FROG '<'

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

int canJump (char *frogs, int frogIndex, int jump, char correctType) {
    int jumpEndIndex = frogIndex + jump;
    char jumpEnd = frogs[jumpEndIndex];

    return frogs[frogIndex] == correctType && jumpEnd == EMPTY_SPACE;
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

    if(canJump(top(*root), emptyIndex - 1, 1, LEFT_FROG))
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
    if(canJump(top(*root), emptyIndex + 1, -1, RIGHT_FROG))
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
    if(canJump(top(*root), emptyIndex - 2, 2, LEFT_FROG))
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
    if(canJump(top(*root), emptyIndex + 2, -2, RIGHT_FROG))
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
