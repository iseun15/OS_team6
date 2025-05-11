#include "team6.h"

// 전역 변수 정의 (team6.h에서 extern 선언됨)
TreeNode* lp = NULL;
char* arg[10];

time_t ltime;
struct tm* Now;
UserList* UsersList = NULL;
FILE* User = NULL;
FILE* Dir = NULL;
DTree* Linux = NULL;
Stack* dStack = NULL;

int main() {
    // 디렉토리 트리 초기화
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(root->name, "/");
    root->type = 'd';
    root->LeftChild = NULL;
    root->RightChild = NULL;
    root->Parent = NULL;
    root->mode = 0755;
    ModeToPermission(root);
    root->UID = 0;
    root->GID = 0;

    Linux = (DTree*)malloc(sizeof(DTree));
    Linux->root = root;
    Linux->current = root;

    lp = root;
    dStack = StackInitialization();

    // 사용자 정보 불러오기 + 로그인
    UsersList = UserListLoad();
    Login(UsersList, Linux);

    char input[MAX_LENGTH];

    while (1) {
        printf("\n$ ");
        if (!fgets(input, sizeof(input), stdin)) break;
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) break;

        if (strncmp(input, "adduser", 7) == 0) {
            char* args = input + 7;
            while (*args == ' ') args++;
            adduser(args, Linux, UsersList);
            continue;
        }

        if (strncmp(input, "cat", 3) == 0) {
            // 명령어 분리
            int i = 0;
            char* token = strtok(input, " ");
            while (token && i < 10) {
                arg[i++] = token;
                token = strtok(NULL, " ");
            }
            cat();  // arg는 전역
            continue;
        }
        if (strcmp(input, "clear") == 0) {
            clear();  // ✅ clear 함수 호출
            continue;
        }
        if (strncmp(input, "head", 4) == 0) {
            int i = 0;
            char* token = strtok(input, " ");
            while (token && i < 10) {
                arg[i++] = token;
                token = strtok(NULL, " ");
            }
            arg[i] = NULL;
            head();
            continue;
        }

        if (strncmp(input, "tail", 4) == 0) {
            int i = 0;
            char* token = strtok(input, " ");
            while (token && i < 10) {
                arg[i++] = token;
                token = strtok(NULL, " ");
            }
            arg[i] = NULL;
            tail();
            continue;
        }

        printf("알 수 없는 명령어입니다.\n");
    }

    UserListSave(UsersList);
    return 0;
}
