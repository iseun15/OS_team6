#include "team6.h"

TreeNode* lp = NULL;
char* arg[10];

void cat() {
	TreeNode* temp = lp->LeftChild;
	int cnt = 0;
	time_t timer = time(NULL);

	if (!strcmp(">", arg[1])) {
		char sentence[1000] = { 0 };
		char c;
		int i = 0;

		while (1) {
			c = getchar();
			if (c == EOF) {
				sentence[i] = '\0';
				break;
			}
			sentence[i++] = c;
		}

		i = 0;
		while (sentence[i] != '\0') {
			if (sentence[i] == '\n') cnt++;
			i++;
		}

		TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
		if (newNode == NULL) return;

		newNode->type = '-';
		strcpy(newNode->name, arg[2]);
		newNode->contents = strdup(sentence); // strdup로 복사
		newNode->line = cnt;
		newNode->LeftChild = NULL;
		newNode->RightChild = NULL;
		newNode->parent = lp;
		newNode->owner = strdup("user");
		newNode->group = strdup("user");
		newNode->time = localtime(&timer);
		newNode->mode[0] = 6;
		newNode->mode[1] = 6;
		newNode->mode[2] = 4;

		if (temp == NULL) {
			lp->LeftChild = newNode;
		} else {
			while (temp->RightChild)
				temp = temp->RightChild;
			temp->RightChild = newNode;
		}
	} 
	else {
		if (!strcmp("-n", arg[1])) {
			while (temp) {
				if (!strcmp(temp->name, arg[2])) {
					char* strCopy = strdup(temp->contents);
					char* token = strtok(strCopy, "\n");
					for (int l = 1; l <= temp->line && token; l++) {
						printf("\t%d  %s\n", l, token);
						token = strtok(NULL, "\n");
					}
					free(strCopy);
					return;
				}
				temp = temp->RightChild;
			}
			printf("현재 디렉토리에서 %s 이름을 가진 파일을 찾을 수 없음\n", arg[2]);
		} 
		else {
			while (temp) {
				if (!strcmp(temp->name, arg[1])) {
					printf("%s", temp->contents);
					return;
				}
				temp = temp->RightChild;
			}
			printf("현재 디렉토리에서 %s 이름을 가진 파일을 찾을 수 없음\n", arg[1]);
		}
	}
}

int main(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        arg[i] = argv[i];
    }

    // 예시: 현재 디렉토리를 가리키는 노드 설정
    TreeNode root;
    memset(&root, 0, sizeof(TreeNode));
    strcpy(root.name, "/");
    root.type = 'd';
    lp = &root;

    cat(); // cat 함수 실행

    return 0;
}