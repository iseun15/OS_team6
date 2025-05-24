#include <stdio.h>
#include <string.h>
#include "team6.h"


// 전역 변수 정의
pthread_mutex_t tree_mutex = PTHREAD_MUTEX_INITIALIZER;
TreeNode* lp = NULL;
char* arg[10];

time_t ltime;
struct tm* Now;
UserList* UsersList = NULL;
FILE* User = NULL;
FILE* Dir = NULL;
DTree* Linux = NULL;
Stack* dStack = NULL;

// 테스트용 파일 경로
#define DIR_FILE "Dir.txt"

void SaveNode(TreeNode* node) {
    if (!node) return;

    FILE* fp = fopen(DIR_FILE, "a");  // append 모드로 열기
    if (!fp) {
        perror("파일 열기 실패");
        return;
    }

    fprintf(fp, "%s\n", node->name);       // 파일 이름
    fprintf(fp, "%d\n", node->line);       // 줄 수
    fprintf(fp, "%s", node->contents);     // 내용
    if (node->contents[strlen(node->contents) - 1] != '\n') {
        fprintf(fp, "\n");  // 마지막 줄 개행이 없으면 추가
    }
    fprintf(fp, "===END===\n");            // 구분자

    fclose(fp);
}

// LoadNodes 함수 정의 (외부에서 사용할 수 있도록 static 제거)
void LoadNodes(void) {
    FILE* fp = fopen(DIR_FILE, "r");
    if (!fp) return;

    while (!feof(fp)) {
        TreeNode* node = calloc(1, sizeof(TreeNode));
        char buf[1000] = {0};
        char linebuf[256];

        if (!fgets(linebuf, sizeof(linebuf), fp)) break;
        linebuf[strcspn(linebuf, "\n")] = 0;
        strcpy(node->name, linebuf);

        if (fscanf(fp, "%d\n", &node->line) != 1) {
            free(node);
            break;
        }

        while (fgets(linebuf, sizeof(linebuf), fp)) {
            if (strcmp(linebuf, "===END===\n") == 0) break;
            strcat(buf, linebuf);
        }

        node->contents = strdup(buf);
        node->type = '-';
        node->Parent = lp;

        // 연결
        if (!lp->LeftChild)
            lp->LeftChild = node;
        else {
            TreeNode* t = lp->LeftChild;
            while (t->RightChild) t = t->RightChild;
            t->RightChild = node;
        }
    }

    fclose(fp);
}
