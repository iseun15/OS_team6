#include "team6.h"

// mkdir 명령어에서 사용하는 시간 관련 전역 변수 정의
// team6.h에 extern 되어 있음
time_t ltime;
struct tm* Now;

// 디렉토리 하나 생성 함수
int MakeDir(DTree* dirTree, char* dirName, char type) {
    TreeNode* NewNode = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode* tmpNode = NULL;

    if (!NewNode) {
        perror("memory allocation failed");
        return -1;
    }

    if (OwnPermission(dirTree->current, 'w') != 0) {
        printf("mkdir: '%s' unable to make directory: access denied\n", dirName);
        free(NewNode);
        return -1;
    }

    if (strcmp(dirName, ".") == 0 || strcmp(dirName, "..") == 0) {
        printf("mkdir: '%s' unable to make directory\n", dirName);
        free(NewNode);
        return -1;
    }

    tmpNode = DirExistion(dirTree, dirName, type);
    if (tmpNode != NULL && tmpNode->type == 'd') {
        printf("mkdir: '%s' unable to make directory: already exist\n", dirName);
        free(NewNode);
        return -1;
    }

    time(&ltime);
    Now = localtime(&ltime);

    strncpy(NewNode->name, dirName, MAX_NAME);
    NewNode->type = type;
    NewNode->mode = (type == 'd') ? 755 : 644;
    NewNode->SIZE = (type == 'd') ? 4096 : 0;
    NewNode->UID = UsersList->current->UID;
    NewNode->GID = UsersList->current->GID;
    NewNode->month = Now->tm_mon + 1;
    NewNode->day = Now->tm_mday;
    NewNode->hour = Now->tm_hour;
    NewNode->min = Now->tm_min;
    NewNode->Parent = dirTree->current;
    NewNode->LeftChild = NULL;
    NewNode->RightSibling = NULL;

    ModeToPermission(NewNode);

    if (dirTree->current->LeftChild == NULL) {
        dirTree->current->LeftChild = NewNode;
    } else {
        tmpNode = dirTree->current->LeftChild;
        while (tmpNode->RightSibling != NULL)
            tmpNode = tmpNode->RightSibling;
        tmpNode->RightSibling = NewNode;
    }

    return 0;
}

// 스레드에서 호출될 함수
void* mkdir_thread(void* arg) {
    ThreadTag* t = (ThreadTag*)arg;
    MakeDir(t->MultiDTree, t->AddValues, 'd');
    pthread_exit(NULL);
}

// 명령어로 받은 여러 디렉토리를 멀티스레딩으로 생성
int Mkdir(DTree* dirTree, char* cmd) {
    if (cmd == NULL || strlen(cmd) == 0) {
        printf("mkdir: wrong input.\n");
        return -1;
    }

    pthread_t threads[MAX_THREAD];
    ThreadTag args[MAX_THREAD];
    int threadCount = 0;

    char* token = strtok(cmd, " ");
    while (token != NULL && threadCount < MAX_THREAD) {
        if (strcmp(token, ".") == 0 || strcmp(token, "..") == 0) {
            printf("mkdir: '%s' unable to make.\n", token);
        } else {
            args[threadCount].MultiDTree = dirTree;
            args[threadCount].AddValues = strdup(token);

            if (pthread_create(&threads[threadCount], NULL, mkdir_thread, (void*)&args[threadCount]) != 0) {
                perror("thread creation failed");
                free(args[threadCount].AddValues);
                return -1;
            }

            threadCount++;
        }
        token = strtok(NULL, " ");
    }

    for (int i = 0; i < threadCount; i++) {
        pthread_join(threads[i], NULL);
        free(args[i].AddValues);
    }

    return 0;
}