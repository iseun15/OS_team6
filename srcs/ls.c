#include "team6.h"

// 파일 정보 출력 함수
void PrintFileInfo(TreeNode* node) {
    // 권한 정보 출력
    PermissionPrint(node);
    printf(" %d %d %4d-%02d-%02d %02d:%02d %s\n", 
           node->UID, node->GID, 
           node->month, node->day, node->hour, node->min, 
           node->name);
}

// ls 명령어 구현
void ls(const char* option) {
    TreeNode* node = Linux->current->LeftChild;

    // 옵션 처리
    int showHidden = 0;
    int detailed = 0;
    if (option != NULL) {
        if (strcmp(option, "-a") == 0) showHidden = 1;
        if (strcmp(option, "-l") == 0) detailed = 1;
        if (strcmp(option, "-al") == 0 || strcmp(option, "-la") == 0) {
            showHidden = 1;
            detailed = 1;
        }
    }

    while (node) {
        // 숨김 파일 처리
        if (!showHidden && node->name[0] == '.') {
            node = node->RightChild;
            continue;
        }

        // 상세 정보 표시 여부
        if (detailed) {
            PrintFileInfo(node);
        } else {
            printf("%s  ", node->name);
        }

        node = node->RightChild;
    }

    if (!detailed) printf("\n");
}