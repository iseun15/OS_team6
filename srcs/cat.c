#include "team6.h"

void cat(char* args) {
    pthread_t tid;
    if (!args || strlen(args) == 0) {
        printf("cat: 파일 이름이 필요합니다.\n");
        return;
    }

    char* input_copy = strdup(args);
    char* argv[4] = {NULL};
    int argc = 0;

    char* token = strtok(input_copy, " ");
    while (token && argc < 4) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }

    pthread_mutex_lock(&tree_mutex);
    for (int i = 0; i < argc; i++) arg[i] = argv[i];
    pthread_mutex_unlock(&tree_mutex);

    if (pthread_create(&tid, NULL, cat_worker, arg) != 0) {
        perror("cat: 스레드 생성 실패");
        free(input_copy);
        return;
    }
    pthread_join(tid, NULL);
    free(input_copy);
}

void* cat_worker(void* arg_ptr) {
    if (!lp) {
        printf("cat: 현재 디렉토리가 초기화되지 않았습니다.\n");
        return NULL;
    }

    TreeNode* temp = lp->LeftChild;
    char** argv = (char**)arg_ptr;

    if (!argv[0]) {
        printf("cat: 인자가 필요합니다.\n");
        return NULL;
    }

    if (!strcmp(argv[0], ">")) {
        if (!argv[1]) {
            printf("cat: 파일 이름이 필요합니다.\n");
            return NULL;
        }

        char sentence[1000] = {0};
        char line[256];
        char* owner = "user";
        char* group = "user";
        int i = 0, cnt = 0;

        while (fgets(line, sizeof(line), stdin)) {
            for (int j = 0; line[j] != '\0' && i < sizeof(sentence) - 1; j++) {
                sentence[i++] = line[j];
                if (line[j] == '\n') cnt++;
            }
        }
        sentence[i] = '\0';
        clearerr(stdin);

        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        if (!newNode) return NULL;

        newNode->type = '-';
        strncpy(newNode->name, argv[1], MAX_NAME - 1);
        newNode->name[MAX_NAME - 1] = '\0';
        newNode->contents = strdup(sentence);
        newNode->line = cnt;
        newNode->LeftChild = NULL;
        newNode->RightChild = NULL;
        newNode->Parent = lp;
        newNode->owner = strdup(owner);
        newNode->group = strdup(group);

        time_t timer = time(NULL);
        newNode->time = localtime(&timer);
        newNode->mode = 0644;
        ModeToPermission(newNode);

        if (!lp->LeftChild) {
            lp->LeftChild = newNode;
        } else {
            while (temp->RightChild)
                temp = temp->RightChild;
            temp->RightChild = newNode;
        }
        SaveNode(newNode);
    }
    else if (!strcmp(argv[0], "-n")) {
        if (!argv[1]) {
            printf("cat: 파일 이름이 필요합니다.\n");
            return NULL;
        }

        while (temp) {
            if (!strcmp(temp->name, argv[1])) {
                char* copy = strdup(temp->contents);
                char* token = strtok(copy, "\n");
                for (int l = 1; token && l <= temp->line; l++) {
                    printf("\t%d  %s\n", l, token);
                    token = strtok(NULL, "\n");
                }
                free(copy);
                return NULL;
            }
            temp = temp->RightChild;
        }
        printf("cat: 현재 디렉토리에서 '%s' 파일을 찾을 수 없습니다.\n", argv[1]);
    }
    else {
        while (temp) {
            if (!strcmp(temp->name, argv[0])) {
                printf("%s", temp->contents);
                return NULL;
            }
            temp = temp->RightChild;
        }
        printf("cat: 현재 디렉토리에서 '%s' 파일을 찾을 수 없습니다.\n", argv[0]);
    }
    return NULL;
}
