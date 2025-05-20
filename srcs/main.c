#include "team6.h"

pthread_mutex_t tree_mutex = PTHREAD_MUTEX_INITIALIZER;

// 전역 변수 정의
UserList* UsersList = NULL;
FILE* User = NULL;
FILE* Dir = NULL;
DTree* Linux = NULL;
Stack* dStack = NULL;
pthread_mutex_t dir_mutex = PTHREAD_MUTEX_INITIALIZER;
TreeNode* lp = NULL;
char* arg[10];
time_t ltime;
struct tm* Now;

int main() {
    // 사용자 및 디렉토리 초기화
    UsersList = UserListLoad();
    if (!UsersList) {
        printf("[ERROR] 사용자 정보를 불러오지 못했습니다.\n");
        return 1;
    }

    TreeNode* root = malloc(sizeof(TreeNode));
    memset(root, 0, sizeof(TreeNode));
    strcpy(root->name, "/");
    root->type = 'd';
    root->UID = 0;
    root->mode = 755;
    ModeToPermission(root);

    Linux = malloc(sizeof(DTree));
    Linux->root = root;
    Linux->current = root;

    Dir = fopen("log.txt", "w");
    dStack = StackInitialization();

    Login(UsersList, Linux);

    printf("\n== 간이 Shell 시뮬레이터 시작 ==\n");
    printf("도움말: mkdir / ls / mv / rmdir / adduser / cd / chmod / echo / pwd / cat / head / tail / clear / exit\n");

    char input[256];
    while (1) {
        printf("\n$ ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strncmp(input, "exit", 4) == 0) break;
        else if (strncmp(input, "mkdir", 5) == 0)
            Mkdir(Linux, input + 6);
        else if (strncmp(input, "rmdir", 5) == 0)
            rmdir_cmd(Linux, input + 6);
        else if (strncmp(input, "mv", 2) == 0)
            mv(Linux, input + 3);
        else if (strncmp(input, "ls", 2) == 0)
            ls(input + 3);
        else if (strncmp(input, "adduser", 7) == 0)
            adduser(input + 8, Linux, UsersList);
        else if (strncmp(input, "cd", 2) == 0)
            cd(input + 3);
        else if (strncmp(input, "chmod", 5) == 0)
            chmod_(Linux, input + 6);
        else if (strncmp(input, "echo", 4) == 0)
            echo(input + 5);
        else if (strncmp(input, "pwd", 3) == 0)
            pwd(Linux, dStack, input + 4);
        else if (strncmp(input, "cat", 3) == 0)
            cat(); // 내부에 사용자 선택이 있거나 입력을 받는 구조일 것
        else if (strncmp(input, "head", 4) == 0)
            head();
        else if (strncmp(input, "tail", 4) == 0)
            tail();
        else if (strncmp(input, "clear", 5) == 0)
            clear();
        else
            printf("[오류] 알 수 없는 명령어입니다: %s\n", input);
    }

    // 종료 시 자원 정리
    UserListSave(UsersList);
    fclose(Dir);
    FreeStack(dStack);
    free(UsersList);
    free(root);
    free(Linux);
    return 0;
}
