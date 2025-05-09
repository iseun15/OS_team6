#include "team6.h"

extern TreeNode* lp;
extern char* arg[];

void head() {
    TreeNode* temp = lp->lchild;
    int line_to_print = 10;

    int i = 1;

    // 옵션 -n 처리
    if (arg[1] && !strcmp(arg[1], "-n")) {
        if (arg[2] == NULL || arg[3] == NULL) {
            printf("사용법: head -n 줄수 파일이름\n");
            return;
        }
        line_to_print = atoi(arg[2]); // 줄 수 파싱
        if (line_to_print <= 0) {
            printf("줄 수는 1 이상이어야 합니다.\n");
            return;
        }

        // 파일 탐색
        while (temp) {
            if (!strcmp(temp->name, arg[3])) {
                char* copy = strdup(temp->contents);
                char* token = strtok(copy, "\n");
                while (token && i <= line_to_print) {
                    printf("%s\n", token);
                    token = strtok(NULL, "\n");
                    i++;
                }
                free(copy);
                return;
            }
            temp = temp->rsibling;
        }

        printf("현재 디렉토리에서 %s 파일을 찾을 수 없습니다.\n", arg[3]);
    }
    else {
        // 파일명 바로 입력: 기본 10줄 출력
        if (arg[1] == NULL) {
            printf("사용법: head [-n 줄수] 파일이름\n");
            return;
        }

        while (temp) {
            if (!strcmp(temp->name, arg[1])) {
                char* copy = strdup(temp->contents);
                char* token = strtok(copy, "\n");
                while (token && i <= line_to_print) {
                    printf("%s\n", token);
                    token = strtok(NULL, "\n");
                    i++;
                }
                free(copy);
                return;
            }
            temp = temp->rsibling;
        }

        printf("현재 디렉토리에서 %s 파일을 찾을 수 없습니다.\n", arg[1]);
    }
}
