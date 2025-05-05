#include "team6.h"

//로그인
void Login(UserList* userList, DTree* dTree) {
    UserNode* user = NULL;
    char userName[MAX_NAME];
    char password[MAX_PASSWORD];

    // 사용자 목록 
    printf("\nUsers:\n");
    for (user = userList->head; user != NULL; user = user->LinkNode) {
        printf("- %s\n", user->name);
    }

    while (1) {
        // ID 입력
        printf("\nLogin as: ");
        fgets(userName, sizeof(userName), stdin);
        userName[strcspn(userName, "\n")] = '\0';

        if (strcmp(userName, "exit") == 0)
            exit(0);

        user = userList->head;
        while (user != NULL) {
            if (strcmp(user->name, userName) == 0) {
                while (1) {
                    //password 입력
                    printf("Password: ");
                    fgets(password, sizeof(password), stdin);
                    password[strcspn(password, "\n")] = '\0';

                    if (strcmp(password, "exit") == 0)
                        exit(0);

                    if (strcmp(user->password, password) == 0) {
                        userList->current = user;
                        MovePath(dTree, user->dir);
                        printf("Successful. Welcome, %s.\n", user->name);
                        return;
                    }
                    //잘못된 password
                    printf("Incorrect password. Try again.\n");
                }
            }
            user = user->LinkNode;  
        }

        printf("User not found. Try again.\n");
    }
}


//파일에서 사용자 정보 불러오기
UserList* UserListLoad() {
    FILE* fp = fopen("./resources/User.txt", "r");
    if (!fp) {
        perror("User.txt open failed");
        return NULL;
    }

    UserList* list = (UserList*)malloc(sizeof(UserList));
    if (!list) return NULL;

    list->head = list->tail = list->current = NULL;
    list->tUID = list->tGID = 0;

    char line[MAX_LENGTH];
    while (fgets(line, sizeof(line), fp)) {
        UserNode* user = (UserNode*)malloc(sizeof(UserNode));
        if (!user) continue;

        // 사용자 정보 읽기
        if (sscanf(line, "%s %s %s %d %d %d %d %d %d %d %d %d",
                   user->name, user->password, user->dir,
                   &user->UID, &user->GID,
                   &user->year, &user->month, &user->day, &user->wday,
                   &user->hour, &user->min, &user->sec) != 12) {
            free(user);
            continue;
        }

        user->LinkNode = NULL;

        // 리스트에 노드 추가
        if (!list->head)
            list->head = list->tail = user;
        else {
            list->tail->LinkNode = user;
            list->tail = user;
        }

        // UID, GID 최신화
        if (user->UID > list->tUID) list->tUID = user->UID;
        if (user->GID > list->tGID) list->tGID = user->GID;
    }

    fclose(fp);
    return list;
}

//사용자 정보 저장 (User.txt에)
void UserListSave(UserList* list) {
    FILE* fp = fopen("./resources/User.txt", "w");
    if (!fp) {
        perror("User.txt save failed");
        return;
    }

    time(&ltime);                    // 현재 시간
    Now = localtime(&ltime);

    UserNode* user = list->head;
    while (user) {
        // 시간 정보 업데이트
        user->year = Now->tm_year + 1900;
        user->month = Now->tm_mon + 1;
        user->day = Now->tm_mday;
        user->wday = Now->tm_wday;
        user->hour = Now->tm_hour;
        user->min = Now->tm_min;
        user->sec = Now->tm_sec;

        fprintf(fp, "%s %s %s %d %d %d %d %d %d %d %d %d\n",
                user->name, user->password, user->dir,
                user->UID, user->GID,
                user->year, user->month, user->day, user->wday,
                user->hour, user->min, user->sec);

        user = user->LinkNode;
    }

    fclose(fp);
}

//사용자 존재 확인
UserNode* ExistUser(UserList* list, const char* name) {
    UserNode* user = list->head;
    while (user) {
        if (strcmp(user->name, name) == 0)
            return user;
        user = user->LinkNode;
    }
    return NULL;
}


//권한 관리
int OwnPermission(TreeNode* node, char mode) {
    if (!node || !UsersList || !UsersList->current) return -1;
    if (UsersList->current->UID == 0) return 0;  // root는 무조건 허용

    int group = 2; // 기본값: others
    if (UsersList->current->UID == node->UID) group = 0;      // owner
    else if (UsersList->current->GID == node->GID) group = 1; // group

    int offset = -1;
    switch (mode) {
        case 'r': offset = 0; break;
        case 'w': offset = 1; break;
        case 'x': offset = 2; break;
        default: return -1; // 잘못된 mode 입력
    }

    int index = group * 3 + offset;
    return (node->permission[index] == 1) ? 0 : -1;
}
