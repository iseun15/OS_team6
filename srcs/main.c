/*
//최종 mkdir UTM 테스트용
#include "team6.h"

// 전역 변수 정의
UserList* UsersList = NULL;
FILE* User = NULL;
FILE* Dir = NULL;
DTree* Linux = NULL;
Stack* dStack = NULL;
pthread_mutex_t tree_mutex = PTHREAD_MUTEX_INITIALIZER;
TreeNode* lp = NULL;
char* arg[10];
time_t ltime;
struct tm* Now;
*/

// int main() {
//     // 사용자 초기화
//     UsersList = malloc(sizeof(UserList));
//     if (!UsersList) {
//         fprintf(stderr, "[ERROR] UsersList malloc 실패\n");
//         return 1;
//     }

//     UsersList->current = malloc(sizeof(UserNode));
//     if (!UsersList->current) {
//         fprintf(stderr, "[ERROR] UsersList->current malloc 실패\n");
//         return 1;
//     }

//     UsersList->current->UID = 1000;
//     UsersList->current->GID = 1000;
//     strcpy(UsersList->current->name, "testuser");

//     // 디렉토리 트리 초기화
//     TreeNode* root = malloc(sizeof(TreeNode));
//     if (!root) {
//         fprintf(stderr, "[ERROR] root malloc 실패\n");
//         return 1;
//     }
//     memset(root, 0, sizeof(TreeNode));
//     strcpy(root->name, "/");
//     root->type = 'd';
//     root->UID = 1000;  // 사용자와 동일하게 설정
//     root->mode = 755;
//     ModeToPermission(root);  // 반드시 호출!

//     DTree dirTree;
//     dirTree.root = root;
//     dirTree.current = root;

//     // Linux 전역 포인터에 복사
//     Linux = malloc(sizeof(DTree));
//     *Linux = dirTree;

//     // Dir 파일 포인터 초기화 (TakePath 등에서 사용 가능)
//     Dir = fopen("log.txt", "w");
//     if (!Dir) {
//         perror("log.txt 파일 열기 실패");
//         return 1;
//     }

//     // 스택 초기화
//     dStack = StackInitialization();

//     // 디렉토리 생성 실행
//     printf("디렉토리 여러 개를 생성합니다...\n");

//     char cmd_buffer[256];
//     strcpy(cmd_buffer, "dir1 dir2 dir3");

//     Mkdir(&dirTree, cmd_buffer);

//     // 결과 출력
//     TreeNode* node = dirTree.current->LeftChild;
//     while (node != NULL) {
//         printf("생성된 디렉토리: %s (UID: %d, mode: %d)\n", node->name, node->UID, node->mode);
//         node = node->RightChild;
//     }

//     // 메모리 정리
//     fclose(Dir);
//     FreeStack(dStack);
//     free(UsersList->current);
//     free(UsersList);
//     free(root);
//     free(Linux);

//     return 0;
// }

//최종 chmod UTM 테스트용
// int main() {
//     // 사용자 초기화
//     UsersList = malloc(sizeof(UserList));
//     UsersList->current = malloc(sizeof(UserNode));
//     UsersList->current->UID = 1000;
//     UsersList->current->GID = 1000;
//     strcpy(UsersList->current->name, "testuser");

//     // 루트 디렉토리 초기화
//     TreeNode* root = malloc(sizeof(TreeNode));
//     memset(root, 0, sizeof(TreeNode));
//     strcpy(root->name, "/");
//     root->type = 'd';
//     root->UID = 1000;
//     root->mode = 755;
//     ModeToPermission(root);

//     DTree dirTree;
//     dirTree.root = root;
//     dirTree.current = root;

//     Linux = malloc(sizeof(DTree));
//     *Linux = dirTree;

//     Dir = fopen("log.txt", "w");
//     dStack = StackInitialization();

//     // 디렉토리 생성
//     printf("디렉토리 생성 중...\n");
//     char mkdir_cmd[256] = "mydir";
//     Mkdir(&dirTree, mkdir_cmd);

//     // 생성된 디렉토리의 권한 확인
//     TreeNode* node = DirExistion(&dirTree, "mydir", 'd');
//     if (node) {
//         printf("mydir 생성 완료, 기존 권한: ");
//         PermissionPrint(node);
//         printf("\n");
//     }

//     // chmod 테스트
//     printf("mydir 권한을 700으로 변경합니다...\n");
//     char chmod_cmd[256] = "700 mydir"; //이전에는 char chmod_cmd[256]="chmod 700 mydir"이어서 UTM에서 오류
//     chmod_(&dirTree, chmod_cmd);

//     // 변경된 권한 확인
//     if (node) {
//         printf("변경된 권한: ");
//         PermissionPrint(node);
//         printf("\n");
//     }

//     // 정리
//     fclose(Dir);
//     FreeStack(dStack);
//     free(UsersList->current);
//     free(UsersList);
//     free(root);
//     free(Linux);

//     return 0;
// }

//pwd 테스트용
// int main() {
//     // 사용자 초기화
//     UsersList = malloc(sizeof(UserList));
//     UsersList->current = malloc(sizeof(UserNode));
//     UsersList->current->UID = 1000;
//     UsersList->current->GID = 1000;
//     strcpy(UsersList->current->name, "testuser");

//     // 디렉토리 트리 초기화
//     TreeNode* root = malloc(sizeof(TreeNode));
//     memset(root, 0, sizeof(TreeNode));
//     strcpy(root->name, "/");
//     root->type = 'd';
//     root->UID = 1000;
//     root->mode = 755;
//     ModeToPermission(root);

//     DTree dirTree;
//     dirTree.root = root;
//     dirTree.current = root;

//     Linux = malloc(sizeof(DTree));
//     *Linux = dirTree;

//     Dir = fopen("log.txt", "w");
//     dStack = StackInitialization();

//     // 디렉토리 생성 및 현재 디렉토리 이동
//     printf("디렉토리 생성 중...\n");
//     char cmd_buffer[256];
//     strcpy(cmd_buffer, "dirA");
//     Mkdir(&dirTree, cmd_buffer);

//     TreeNode* sub = DirExistion(&dirTree, "dirA", 'd');
//     if (sub) {
//         dirTree.current = sub;  // 디렉토리 이동
//         printf("dirA로 이동 완료.\n");
//     }

//     // 현재 경로 출력
//     printf("현재 경로 (pwd): ");
//     pwd(&dirTree, dStack, NULL);

//     // 메모리 정리
//     fclose(Dir);
//     FreeStack(dStack);
//     free(UsersList->current);
//     free(UsersList);
//     free(root);
//     free(Linux);

//     return 0;
// }

/*
int main() {
    // DTree 초기화
    Linux = (DTree*)malloc(sizeof(DTree));
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->Parent = NULL;
    root->LeftChild = NULL;
    root->RightChild = NULL;
    root->name[0] = '/';
    root->name[1] = '\0';
    Linux->root = root;
    Linux->current = root;

    // 테스트용 파일 노드 추가
    TreeNode* file1 = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(file1->name, "file1.txt");
    file1->RightChild = NULL;
    file1->LeftChild = NULL;
    file1->name[0] = 'f'; file1->name[1] = 'i'; file1->name[2] = 'l'; file1->name[3] = 'e'; file1->name[4] = '1'; file1->name[5] = '\0';
    file1->UID = 1000;
    file1->GID = 1000;
    file1->month = 5;
    file1->day = 10;
    file1->hour = 14;
    file1->min = 30;

    TreeNode* file2 = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(file2->name, ".hiddenfile");
    file2->RightChild = NULL;
    file2->LeftChild = NULL;
    file2->UID = 1000;
    file2->GID = 1000;
    file2->month = 5;
    file2->day = 10;
    file2->hour = 15;
    file2->min = 00;

    // 링크 연결
    root->LeftChild = file1;
    file1->RightChild = file2;

    printf("== 기본 ls 실행 ==\n");
    ls(NULL);

    printf("\n== ls -a 실행 ==\n");
    ls("-a");

    printf("\n== ls -l 실행 ==\n");
    ls("-l");

    printf("\n== ls -al 실행 ==\n");
    ls("-al");

    return 0;
}
*/


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

    printf("== 간이 Shell 시뮬레이터 시작 ==\n");
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
