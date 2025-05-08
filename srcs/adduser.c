#include "team6.h"

void adduser(char* argument, DTree* dirtree, UserList* userlist) {
    time_t timer = time(NULL);
    struct tm* t = localtime(&timer);

    int newUID = userlist->tUID + 1;
    int newGID = userlist->tGID + 1;
    char* newName = NULL;

    int setUID = 0, setGID = 0;

    char* token = strtok(argument, " ");
    while (token) {
        if (strcmp(token, "-u") == 0) {
            token = strtok(NULL, " ");
            if (!token) { printf("adduser: Missing UID\n"); return; }
            newUID = atoi(token);
            setUID = 1;
        } else if (strcmp(token, "-g") == 0) {
            token = strtok(NULL, " ");
            if (!token) { printf("adduser: Missing GID\n"); return; }
            newGID = atoi(token);
            setGID = 1;
        } else {
            newName = token;
            break;
        }
        token = strtok(NULL, " ");
    }

    if (!newName) {
        printf("adduser: Missing username\n");
        return;
    }

    if (ExistUser(userlist, newName)) {
        printf("adduser: User '%s' already exists\n", newName);
        return;
    }

    UserNode* newUser = (UserNode*)malloc(sizeof(UserNode));
    if (!newUser) {
        perror("adduser: malloc failed");
        return;
    }

    strncpy(newUser->name, newName, MAX_NAME);
    newUser->name[MAX_NAME - 1] = '\0';
    strcpy(newUser->password, "0000");
    snprintf(newUser->dir, MAX_DIR, "/home/%s", newName);
    newUser->UID = newUID;
    newUser->GID = newGID;
    newUser->year = t->tm_year + 1900;
    newUser->month = t->tm_mon + 1;
    newUser->day = t->tm_mday;
    newUser->wday = t->tm_wday;
    newUser->hour = t->tm_hour;
    newUser->min = t->tm_min;
    newUser->sec = t->tm_sec;
    newUser->LinkNode = NULL;

    if (!userlist->head)
        userlist->head = userlist->tail = newUser;
    else {
        userlist->tail->LinkNode = newUser;
        userlist->tail = newUser;
    }

    if (newUID > userlist->tUID) userlist->tUID = newUID;
    if (newGID > userlist->tGID) userlist->tGID = newGID;

    UserListSave(userlist);

    printf("User '%s' added. (UID: %d, GID: %d, Home: %s)\n", newName, newUID, newGID, newUser->dir);
}
