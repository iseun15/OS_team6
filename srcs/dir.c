#include "team6.h"


//디렉토리 이동
int MovePath(DTree* dTree, const char* path) {
    // 트리나 경로가 NULL이면 실패
    if (!dTree || !path) return -1;

    TreeNode* tmp = dTree->current;  // 이동 실패 시 복구용 백업
    TreeNode* cursor = NULL;         // 경로 따라 이동하는 커서
    char pathCopy[MAX_LENGTH];       // strtok 사용 위해 원본 복사
    char* token;

    // 원본 path를 보호하면서 복사
    strncpy(pathCopy, path, sizeof(pathCopy));
    pathCopy[sizeof(pathCopy) - 1] = '\0';

    if (pathCopy[0] == '/') {  //절대 경로(root 부터)
        cursor = dTree->root;
        token = strtok(pathCopy + 1, "/");  
    } else { //상대경로(현위치부터)
        cursor = dTree->current;
        token = strtok(pathCopy, "/");
    }

    //경로 이동
    while (token != NULL) {
        TreeNode* next = ChangeToSubdirectory(cursor, token);
        if (!next) {
            printf("Directory not found: %s\n", token);
            dTree->current = tmp;
            return -1;
        }
        cursor = next;
        token = strtok(NULL, "/");
    }
    // 이동 성공
    dTree->current = cursor;
    return 0;
}

// 하위 디렉토리로 이동
TreeNode* ChangeToSubdirectory(TreeNode* current, const char* token) {
    if (!current || !token) return NULL;

    // 현재 위치
    if (strcmp(token, ".") == 0) return current;

    // 부모로 이동
    if (strcmp(token, "..") == 0) {
        return current->Parent ? current->Parent : current;
    }

    // 자식 찾기
    TreeNode* child = current->LeftChild;
    while (child != NULL) {
        if (strcmp(child->name, token) == 0 && child->type == 'd') {
            return child;
        }
        child = child->RightChild;
    }

    return NULL;  // 못 찾음
}