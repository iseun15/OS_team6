#include "team6.h"

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
