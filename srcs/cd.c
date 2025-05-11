#include "team6.h"

// 현재 경로 표시 함수
void PrintCurrentPath(DTree* tree) {
    Stack* stack = StackInitialization();
    TakePath(tree, tree->current, stack);
    FreeStack(stack);
}

// cd 명령어: 디렉토리 이동
void cd(const char* path) {
    if (path == NULL || strlen(path) == 0) {
        printf("Usage: cd <directory>\n");
        return;
    }

    // 현재 디렉토리 유지
    if (strcmp(path, ".") == 0) {
        PrintCurrentPath(Linux);
        return;
    }

    // 상위 디렉토리 이동
    if (strcmp(path, "..") == 0) {
        if (Linux->current->Parent != NULL) {
            Linux->current = Linux->current->Parent;
            PrintCurrentPath(Linux);
        } else {
            printf("Already at the root directory.\n");
        }
        return;
    }

    // 경로 이동
    if (MovePath(Linux, path) == 0) {
        PrintCurrentPath(Linux);
    } else {
        printf("cd: no such file or directory: %s\n", path);
    }
}