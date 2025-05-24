#include "team6.h"

// 특수문자 해석 함수
void PrintWithEscapes(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\\' && str[i + 1] != '\0') {
            switch (str[++i]) {
                case 'n':
                    putchar('\n');
                    break;
                case 't':
                    putchar('\t');
                    break;
                case '\\':
                    putchar('\\');
                    break;
                case '\"':
                    putchar('\"');
                    break;
                default:
                    putchar('\\');
                    putchar(str[i]);
                    break;
            }
        } else {
            putchar(str[i]);
        }
    }
}

// echo 명령어 구현
void echo(const char* args) {
    int newline = 1; // 기본적으로 줄바꿈
    int interpret = 0; // 특수문자 해석 여부

    // 옵션 파싱
    if (args != NULL) {
        if (strncmp(args, "-n", 2) == 0) {
            newline = 0;
            args += 2;
            while (*args == ' ') args++;  // 공백 제거
        } else if (strncmp(args, "-e", 2) == 0) {
            interpret = 1;
            args += 2;
            while (*args == ' ') args++;  // 공백 제거
        }
    }

    // 특수문자 해석 여부에 따라 출력
    if (interpret) {
        PrintWithEscapes(args);
    } else {
        printf("%s", args);
    }

    // 줄바꿈 처리
    if (newline) {
        putchar('\n');
    }
}