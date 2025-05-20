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
    TreeNode* target = Linux->current;

    // ls만 입력해도 정상 작동하게게
    if (option != NULL && strlen(option) == 0) {
        option = NULL;
    }

    // 옵션 처리
    int showHidden = 0;
    int detailed = 0;
    
    if (option != NULL) {
            if (strcmp(option, "-a") == 0) showHidden = 1;
            else if (strcmp(option, "-l") == 0) detailed = 1;
            else if (strcmp(option, "-al") == 0 || strcmp(option, "-la") == 0) {
                showHidden = 1;
                detailed = 1;
            } else {
                // 옵션이 아닌 경우: 디렉토리 이름으로 간주
                TreeNode* found = DirExistion(Linux, (char*)option, 'd');
                if (found == NULL) {
                    printf("ls: cannot access '%s': No such directory\n", option);
                    return;
                }
                target = found;
            }
        }

    TreeNode* node = target->LeftChild;
    int fileFound=0;

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
        
        fileFound =1;
        node = node->RightChild;
    }
    if (!fileFound)
        printf("no files in '%s'\n", target->name);

    if (!detailed) printf("\n");
}