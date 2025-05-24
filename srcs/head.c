#include "team6.h"

// TreeNode* lp = NULL;      // 현재 디렉토리
// char* arg[10];            // 명령어 인자 저장용

// 작업 함수: head 명령어 수행
void* head_worker(void* arg_ptr) {
    char** argv = (char**)arg_ptr;
    TreeNode* temp = lp->LeftChild;
    int line_to_print = 10;

    // 옵션 처리: head -n [줄수] [파일이름]
    if (argv[1] && !strcmp(argv[1], "-n")) {
        if (argv[2] == NULL || argv[3] == NULL) {
            printf("사용법: head -n 줄수 파일이름\n");
            return NULL;
        }
        line_to_print = atoi(argv[2]);
        if (line_to_print <= 0) {
            printf("줄 수는 1 이상이어야 합니다.\n");
            return NULL;
        }
        // 파일 탐색
        while (temp) {
            if (!strcmp(temp->name, argv[3])) {
                char* copy = strdup(temp->contents);
                char* token = strtok(copy, "\n");
                int i = 1;
                while (token && i <= line_to_print) {
                    printf("%s\n", token);
                    token = strtok(NULL, "\n");
                    i++;
                }
                free(copy);
                return NULL;
            }
            temp = temp->RightChild;
        }
        printf("현재 디렉토리에서 %s 파일을 찾을 수 없습니다.\n", argv[3]);
    }
    else {
        // 기본 사용: head [파일이름]
        if (argv[1] == NULL) {
            printf("사용법: head [-n 줄수] 파일이름\n");
            return NULL;
        }
        while (temp) {
            if (!strcmp(temp->name, argv[1])) {
                char* copy = strdup(temp->contents);
                char* token = strtok(copy, "\n");
                int i = 1;
                while (token && i <= line_to_print) {
                    printf("%s\n", token);
                    token = strtok(NULL, "\n");
                    i++;
                }
                free(copy);
                return NULL;
            }
            temp = temp->RightChild;
        }
        printf("현재 디렉토리에서 %s 파일을 찾을 수 없습니다.\n", argv[1]);
    }

    return NULL;
}

// head 명령어 함수: 스레드 실행
void head() {
    pthread_t tid;
    if (pthread_create(&tid, NULL, head_worker, arg) != 0) {
        perror("스레드 생성 실패");
        return;
    }
    pthread_join(tid, NULL);
}