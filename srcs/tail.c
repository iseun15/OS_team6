#include "team6.h"

// TreeNode* lp = NULL;
// char* arg[10];

void* tail_worker(void* arg_ptr) {
    char** argv = (char**)arg_ptr;
    TreeNode* temp = lp->LeftChild;
    int line_to_print = 10;
    const char* filename = NULL;

    // 옵션 파싱
    if (argv[1] && !strcmp(argv[1], "-n")) {
        if (!argv[2] || !argv[3]) {
            printf("사용법: tail -n 줄수 파일이름\n");
            return NULL;
        }
        line_to_print = atoi(argv[2]);
        filename = argv[3];
    } else {
        filename = argv[1];
    }

    // 파일 탐색
    while (temp) {
        if (!strcmp(temp->name, filename)) {
            int total_lines = temp->line;
            int skip = total_lines - line_to_print;
            if (skip < 0) skip = 0;

            char* copy = strdup(temp->contents);
            char* token = strtok(copy, "\n");

            // 먼저 skip 줄만큼 건너뜀
            int i = 0;
            while (token && i < skip) {
                token = strtok(NULL, "\n");
                i++;
            }

            // 나머지 출력
            while (token) {
                printf("%s\n", token);
                token = strtok(NULL, "\n");
            }

            free(copy);
            return NULL;
        }
        temp = temp->RightChild;
    }

    printf("현재 디렉토리에서 %s 파일을 찾을 수 없습니다.\n", filename);
    return NULL;
}

void tail() {
    pthread_t tid;
    if (pthread_create(&tid, NULL, tail_worker, arg) != 0) {
        perror("스레드 생성 실패");
        return;
    }
    pthread_join(tid, NULL);
}
