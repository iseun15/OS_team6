#include "team6.h"

// TreeNode* lp = NULL;
// char* arg[10];

void* cat_worker(void* arg_ptr) {
    TreeNode* temp = lp->LeftChild;
    char** argv = (char**)arg_ptr;

    if (!strcmp(argv[1], ">")) {
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
        strcpy(newNode->name, argv[2]);
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
    }
    else {
        if (!strcmp(argv[1], "-n")) {
            while (temp) {
                if (!strcmp(temp->name, argv[2])) {
                    char* token = strtok(strdup(temp->contents), "\n");
                    for (int l = 1; token && l <= temp->line; l++) {
                        printf("\t%d  %s\n", l, token);
                        token = strtok(NULL, "\n");
                    }
                    return NULL;
                }
                temp = temp->RightChild;
            }
            printf("현재 디렉토리에서 %s 이름을 가진 파일을 찾을 수 없음\n", argv[2]);
        } else {
            while (temp) {
                if (!strcmp(temp->name, argv[1])) {
                    printf("%s", temp->contents);
                    return NULL;
                }
                temp = temp->RightChild;
            }
            printf("현재 디렉토리에서 %s 이름을 가진 파일을 찾을 수 없음\n", argv[1]);
        }
    }

    return NULL;
}


void cat() {
    pthread_t tid;
    if (pthread_create(&tid, NULL, cat_worker, arg) != 0) {
        perror("스레드 생성 실패");
        return;
    }
    pthread_join(tid, NULL);
}
