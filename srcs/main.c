#include "team6.h"

int main(int argc, char* argv[]) {
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
    lp = Linux->current;  // ← 중요: lp 초기화

    Dir = fopen("log.txt", "w");
    dStack = StackInitialization();

    Login(UsersList, Linux);

    printf("\n== 간이 Shell 시뮬레이터 시작 ==\n");
    printf("도움말: mkdir / ls / mv / rmdir / adduser / cd / chmod / echo / pwd / cat / tail / clear / exit\n");

    char input[256];
    while (1) {
        printf("\n$ ");
        if (!fgets(input, sizeof(input), stdin)) break;
        input[strcspn(input, "\n")] = '\0';

        char* cmd = strtok(input, " ");
        char* args = strtok(NULL, "");

        if (!cmd) continue;

        if (strcmp(cmd, "exit") == 0)
            break;
        else if (strcmp(cmd, "mkdir") == 0)
            Mkdir(Linux, args);
        else if (strcmp(cmd, "rmdir") == 0)
            rmdir_cmd(Linux, args);
        else if (strcmp(cmd, "mv") == 0)
            mv(Linux, args);
        else if (strcmp(cmd, "ls") == 0)
            ls(args);
        else if (strcmp(cmd, "adduser") == 0)
            adduser(args, Linux, UsersList);
        else if (strcmp(cmd, "cd") == 0)
            cd(args);
        else if (strcmp(cmd, "chmod") == 0)
            chmod_(Linux, args);
        else if (strcmp(cmd, "echo") == 0)
            echo(args);
        else if (strcmp(cmd, "pwd") == 0)
            pwd(Linux, dStack, args);
        else if (strcmp(cmd, "cat") == 0)
            cat(args);
        else if (strcmp(cmd, "tail") == 0)
            tail(args);
        else if (strcmp(cmd, "clear") == 0)
            clear();
        else
            printf("[오류] 알 수 없는 명령어입니다: %s\n", cmd);
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
