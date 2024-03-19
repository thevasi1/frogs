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

//TODO: delete the root argument here and wherever we pass it
struct StackNode *newNode(char *data, struct StackNode **root)
{
    struct StackNode *stackNode = (struct StackNode *)malloc(sizeof(struct StackNode));

    int charSize = strlen(data);
    char *newData;

    newData = (char *)malloc(charSize * sizeof(char));
    strncpy(newData, data, sizeof(data));

    stackNode->data = newData;
    stackNode->next = NULL;
    
    return stackNode;
}

int isEmpty(struct StackNode *root)
{
    return !root;
}

void push(struct StackNode **root, char *data)
{
    struct StackNode *stackNode = newNode(data, root);
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

    printf("%s popped from stack\n", popped);
    free(temp);
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

canLeftDoubleJump(char *frogs, int frogIndex)
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

void rec(struct StackNode** root, char *frogs, int *emptyIndex)
{
    if (!strcmp(frogs, "111_000")){
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

    if(canLeftJump(top(*root), *emptyIndex - 1))
    {
        doJump(frogs, *emptyIndex - 1, emptyIndex);
        push(root, frogs);
        rec(root, frogs, emptyIndex);
        pop(root);
    }
    if(canRightJump(frogs, *emptyIndex + 1))
    {
        doJump(frogs, *emptyIndex + 1, emptyIndex);
        push(root, frogs);
        rec(root, frogs, emptyIndex);
        pop(root);
    }
    // if(canLeftDoubleJump)
    // {
    //     doJump();
    //     push();
    //     rec();
    //     pop();
    // }
    // if(canRightDoubleJump)
    // {
    //     doJump();
    //     push();
    //     rec();
    //     pop();
    // }

    // pop();
}

int main()
{
    struct StackNode* root = NULL;
    int frogsTeam = 2;
    // scanf("%d", &frogsTeam);

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

    int emptyIndex = frogsTeam;

    push(&root, frogs);
    rec(&root, frogs, &emptyIndex);
    while(top(root) != NULL) {
        pop(&root);
    }

    return 0;
}
