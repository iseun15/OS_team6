// #include "team6.h"

// int main() {
//     dStack = StackInitialization();
//     UsersList = UserListLoad();
//     Login(UsersList, Linux);  // Linux는 명령어 구현자들이 연결할 Tree

//     // 루프와 명령어 실행은 다른 팀원이 구현
// }


#include "team6.h"

UserList* UsersList;  // 전역 변수 정의
FILE* User;           // 전역 변수 정의
time_t ltime;
struct tm* Now;
Stack* dStack;

int main() {
    dStack = StackInitialization();
    if (!dStack) {
        printf("❌ Failed to initialize stack.\n");
        return 1;
    }

    // 스택에 경로 push
    Push(dStack, "/");
    Push(dStack, "/home");
    Push(dStack, "/home/user");

    // 스택 내용 출력 (디버깅용)
    PrintStack(dStack);

    // pop 테스트
    char* top = Pop(dStack);
    printf("🔼 Pop: %s\n", top);

    top = Pop(dStack);
    printf("🔼 Pop: %s\n", top);

    PrintStack(dStack);

    return 0;
}
