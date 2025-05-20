#include "team6.h"

void* cat_worker(void* arg_ptr) {
    TreeNode* temp = lp->LeftChild;
    char** argv = (char**)arg_ptr;

    if (!argv[1]) {
        printf("cat: 인자가 필요합니다.\n");
        return NULL;
    }

    if (!strcmp(argv[1], ">")) {
        if (!argv[2]) {
            printf("cat: 파일 이름이 필요합니다.\n");
            return NULL;
        }

        char sentence[1000] = { 0 };
        char line[256];
        char* owner = "user";
        char* group = "user";
        int i = 0;
        int cnt = 0;  

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
        strncpy(newNode->name, argv[2], MAX_NAME - 1);
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

        if (temp == NULL) {
            lp->LeftChild = newNode;
        } else {
            while (temp->RightChild)
                temp = temp->RightChild;
            temp->RightChild = newNode;
        }

        SaveNode(newNode);  // 저장
    }
    else if (!strcmp(argv[1], "-n")) {
        if (!argv[2]) {
            printf("cat: 파일 이름이 필요합니다.\n");
            return NULL;
        }

        while (temp) {
            if (!strcmp(temp->name, argv[2])) {
                char* contents_copy = strdup(temp->contents);
                char* token = strtok(contents_copy, "\n");
                for (int l = 1; token && l <= temp->line; l++) {
                    printf("\t%d  %s\n", l, token);
                    token = strtok(NULL, "\n");
                }
                free(contents_copy);
                return NULL;
            }
            temp = temp->RightChild;
        }
        printf("cat: 현재 디렉토리에서 '%s' 파일을 찾을 수 없습니다.\n", argv[2]);
    }
    else {
        while (temp) {
            if (!strcmp(temp->name, argv[1])) {
                printf("%s", temp->contents);
                return NULL;
            }
            temp = temp->RightChild;
        }
        printf("cat: 현재 디렉토리에서 '%s' 파일을 찾을 수 없습니다.\n", argv[1]);
    }

    return NULL;
}

void cat() {
    pthread_t tid;
    if (pthread_create(&tid, NULL, cat_worker, arg) != 0) {
        perror("cat: 스레드 생성 실패");
        return;
    }
    pthread_join(tid, NULL);
}
