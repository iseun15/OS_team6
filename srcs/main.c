#include "team6.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) arg[i - 1] = argv[i];  // 명령어 인자 정렬

    // 루트 디렉토리 초기화
    lp = calloc(1, sizeof(TreeNode));
    strcpy(lp->name, "/");
    lp->type = 'd';
    lp->mode = 755;

    LoadNodes();  // 기존 Dir.txt에서 노드 불러오기

    if (argc == 1) {
        // ./os_team6_test 단독 실행 시: 입력 대기
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), stdin)) {
            printf("%s", buffer);
        }
        return 0;
    }

    // argv[1] 기준으로 명령어 판단
    if (strcmp(argv[1], "cat") == 0) {
        cat();
    } else if (strcmp(argv[1], "tail") == 0) {
        tail();
    } else if (strcmp(argv[1], "clear") == 0) {
        clear();
    } else {
        printf("알 수 없는 명령입니다: %s\n", argv[1]);
    }

    return 0;
}
