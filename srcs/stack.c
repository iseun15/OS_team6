#include "team6.h"

int IsEmpty(Stack* stack) {
    return (stack == NULL || stack->TopNode == NULL);
}

// 스택 초기화
Stack* StackInitialization() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) {
        perror("Failed to allocate stack");
        return NULL;
    }
    stack->TopNode = NULL;
    return stack;
}

// Push
int Push(Stack* stack, const char* name) {
    if (!stack || !name) return -1;

    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        perror("Failed to allocate stack node");
        return -1;
    }

    strncpy(newNode->name, name, MAX_NAME);
    newNode->name[MAX_NAME - 1] = '\0';  
    newNode->LinkNode = stack->TopNode;
    stack->TopNode = newNode;

    return 0;
}

// Pop
char* Pop(Stack* stack) {
    if (IsEmpty(stack)) return NULL;

    StackNode* temp = stack->TopNode;
    stack->TopNode = temp->LinkNode;

    char* nameCopy = strdup(temp->name);  
    free(temp);
    return nameCopy;
}

// 스택 출력 (디버깅용) / 추후 제거 예정
void PrintStack(Stack* stack) {
    StackNode* current = stack->TopNode;
    printf("📂 Path Stack:\n");
    while (current != NULL) {
        printf(" - %s\n", current->name);
        current = current->LinkNode;
    }
}

// 메모리 해제
void FreeStack(Stack* stack) {
    while (!IsEmpty(stack)) {
        char* temp = Pop(stack);
        free(temp);  
    }
    free(stack);
}