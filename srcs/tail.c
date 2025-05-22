#include "team6.h"
#include <ctype.h>  // for isspace
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim_whitespace(char* str) {
    if (!str) return;

    // 앞뒤 공백 제거
    char* end;
    while (isspace((unsigned char)*str)) str++;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) *end-- = '\0';
    memmove(str, str, strlen(str) + 1);
}

void tail(char* args) {
    if (!args || strlen(args) == 0) {
        printf("tail: 파일 이름이 필요합니다.\n");
        return;
    }

    int num_lines = 10;  // 기본값
    char* filename = NULL;

    // args 복사 후 토큰 분리
    char* arg_copy = strdup(args);
    char* token = strtok(arg_copy, " ");
    while (token) {
        if (strcmp(token, "-n") == 0) {
            token = strtok(NULL, " ");
            if (!token || sscanf(token, "%d", &num_lines) != 1 || num_lines < 1) {
                printf("tail: 유효한 숫자가 필요합니다.\n");
                free(arg_copy);
                return;
            }
        } else {
            filename = token;
        }
        token = strtok(NULL, " ");
    }

    if (!filename) {
        printf("tail: 파일 이름이 필요합니다.\n");
        free(arg_copy);
        return;
    }

    trim_whitespace(filename);

    TreeNode* file = DirExistion(Linux, filename, '-');
    if (!file) {
        printf("tail: 현재 디렉토리에서 '%s' 파일을 찾을 수 없습니다.\n", filename);
        free(arg_copy);
        return;
    }

    if (!file->contents || file->line == 0) {
        printf("tail: '%s' 파일에 내용이 없습니다.\n", filename);
        free(arg_copy);
        return;
    }

    // 줄 분리 및 출력
    char* contents = strdup(file->contents);
    char* lines[1024] = {0};
    int count = 0;

    char* line = strtok(contents, "\n");
    while (line && count < 1024) {
        lines[count++] = line;
        line = strtok(NULL, "\n");
    }

    int start = (count > num_lines) ? count - num_lines : 0;
    for (int i = start; i < count; i++) {
        printf("%s\n", lines[i]);
    }

    free(contents);
    free(arg_copy);
}
