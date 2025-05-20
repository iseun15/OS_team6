#include "team6.h"

void* clear_worker(void* arg) {
    printf("\033[2J\033[H");  // ANSI escape 코드로 화면 클리어
    return NULL;
}

void clear() {
    pthread_t tid;
    if (pthread_create(&tid, NULL, clear_worker, NULL) != 0) {
        perror("스레드 생성 실패");
        return;
    }
    pthread_join(tid, NULL);
}
