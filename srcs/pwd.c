#include "team6.h"

int pwd(DTree* dirTree, Stack* stack, char* cmd) {
    if (cmd == NULL) {
        PrintPath(dirTree, stack);
    } else if (cmd[0] == '-') {
        if (strcmp(cmd, "--help") == 0) {
            printf("manual: pwd\n");
            printf("  printing all path in working directory.\n");
            return 0;
        } else {
            printf("pwd: inappropriate option -- '%s'\n", cmd);
            return -1;
        }
    } else {
        printf("pwd: wrong input.\n");
        return -1;
    }

    return 0;
}

void PrintPath(DTree* tree, Stack* stack) {
    if (tree == NULL || tree->current == NULL) return;

    Stack* temp = StackInitialization();
    TreeNode* node = tree->current;

    // 현재 노드에서 루트까지 경로를 임시 스택에 저장
    while (node != NULL && node->Parent != NULL) {
        Push(temp, node->name);
        node = node->Parent;
    }

    printf("/");

    // 스택에서 pop하면서 경로 출력
    while (!IsEmpty(temp)) {
        printf("%s", Pop(temp));
        if (!IsEmpty(temp)) printf("/");
    }

    printf("\n");

    FreeStack(temp);
}