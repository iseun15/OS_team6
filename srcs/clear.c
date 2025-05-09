#include "team6.h"

void clear() {
    // ANSI escape code: 전체 화면 지우고 커서를 좌측 상단으로 이동
    printf("\033[2J\033[H");
}
