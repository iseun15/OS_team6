#include "team6.h"

// chmod 명령어 구현
int chmod_(DTree* dirTree, char* cmd) {
    if (cmd == NULL) {
        printf("chmod: wrong operator\n");
        return -1;
    }

    char cmdCopy[MAX_LENGTH];
    strncpy(cmdCopy, cmd, MAX_LENGTH);
    cmdCopy[MAX_LENGTH - 1] = '\0';

    char* token = strtok(cmdCopy, " ");
    int recursive = 0;

    // 옵션 판단
    if (strcmp(token, "-R") == 0) {
        recursive = 1;
        token = strtok(NULL, " ");
    }

    // 권한 추출
    if (token == NULL || strlen(token) != 3) {
        printf("chmod: wrong access form (예: 755)\n");
        return -1;
    }

    int mode = strtol(token, NULL, 8); 

    // 대상 이름 추출 및 처리
    char* dirName = strtok(NULL, " ");
    if (dirName == NULL) {
        printf("chmod: no such directory or file name.\n");
        return -1;
    }

    while (dirName != NULL) {
        TreeNode* target = DirExistion(dirTree, dirName, 'd');
        if (!target)
            target = DirExistion(dirTree, dirName, '-');

        if (target) {
            if (OwnPermission(target, 'w') != 0) {
                printf("chmod: '%s' cannot change: access denied\n", dirName);
            } else {
                target->mode = mode;
                ModeToPermission(target);

                if (recursive && target->type == 'd') {
                    ModeConversAll(target->LeftChild, mode);
                }
            }
        } else {
            printf("chmod: '%s': no such file or directory\n", dirName);
        }

        dirName = strtok(NULL, " ");
    }

    return 0;
}