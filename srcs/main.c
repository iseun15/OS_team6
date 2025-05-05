#include "team6.h"

int main() {
    dStack = StackInitialization();
    UsersList = UserListLoad();
    Login(UsersList, Linux);  // Linux는 명령어 구현자들이 연결할 Tree

    // 루프와 명령어 실행은 다른 팀원이 구현
}