//작동 도와주는 함수 모음

#include "team6.h"

//권한 설정 관련
// mode => permission[9] 변환
int ModeToPermission(TreeNode* node) {
    int mode = node->mode;
    char* p = node->permission;

    p[0] = (node->type == 'd') ? 'd' : '-';  // 디렉토리 여부

    // user
    p[1] = (mode & 0400) ? 'r' : '-';
    p[2] = (mode & 0200) ? 'w' : '-';
    p[3] = (mode & 0100) ? 'x' : '-';

    // group
    p[4] = (mode & 0040) ? 'r' : '-';
    p[5] = (mode & 0020) ? 'w' : '-';
    p[6] = (mode & 0010) ? 'x' : '-';

    // others
    p[7] = (mode & 0004) ? 'r' : '-';
    p[8] = (mode & 0002) ? 'w' : '-';
    p[9] = (mode & 0001) ? 'x' : '-';

    p[10] = '\0';  // 문자열 끝
    return 0;
}

//permission => rwxr-xr-- 출력
void PermissionPrint(TreeNode* node) {
    printf("%s", node->permission);
}

// 단일 노드 삭제
void NodeRemove(TreeNode* node) {
    if (node) free(node);
}

// 디렉토리 전체 삭제
void DirRemove(TreeNode* target) {
    TreeNode* parent = target->Parent;
    if (!parent) return;

    TreeNode* current = parent->LeftChild;
    TreeNode* prev = NULL;

    while (current) {
        if (current == target) {
            if (prev == NULL) {
                parent->LeftChild = current->RightChild;
            } else {
                prev->RightChild = current->RightChild;
            }
            break;
        }
        prev = current;
        current = current->RightChild;
    }

    free(target);  // 단일 노드 삭제
}

// 디렉토리에서 이름&타입 일치하는 노드 탐색
TreeNode* DirExistion(DTree* tree, const char* name, char type) {
    TreeNode* cur = tree->current->LeftChild;
    while (cur) {
        if (strcmp(cur->name, name) == 0 && cur->type == type)
            return cur;
        cur = cur->RightChild;
    }
    return NULL;
}

// 경로에서 상위 경로 추출
char* TakeDir(const char* path) {
    static char parent[MAX_DIR];
    char temp[MAX_DIR];
    char* last = NULL;

    strncpy(temp, path, MAX_DIR);
    temp[MAX_DIR - 1] = '\0';

    char* token = strtok(temp, "/");
    parent[0] = '\0';

    while (token) {
        if (last) {
            strcat(parent, "/");
            strcat(parent, last);
        }
        last = token;
        token = strtok(NULL, "/");
    }

    return parent[0] ? parent : "/";
}

//디렉토리 경로 생성 및 출력
void TakePath(DTree* tree, TreeNode* node, Stack* stack) {
    TreeNode* cursor = node->Parent;
    char fullPath[MAX_DIR] = "";

    if (cursor == tree->root) {
        strcpy(fullPath, "/");
    } else {
        while (cursor && cursor != tree->root) {
            Push(stack, cursor->name);
            cursor = cursor->Parent;
        }
        while (!IsEmpty(stack)) {
            strcat(fullPath, "/");
            strcat(fullPath, Pop(stack));
        }
    }
    fprintf(Dir, " %s\n", fullPath);
}

// 재귀적으로 권한 모드 일괄 변경
void ModeConversAll(TreeNode* node, int mode) {
    if (!node) return;
    node->mode = mode;
    ModeToPermission(node);
    ModeConversAll(node->LeftChild, mode);
    ModeConversAll(node->RightChild, mode);
}

// 재귀적으로 소유자/그룹 변경
void ChangeOwnerAll(TreeNode* node, char* userName) {
    if (!node || !userName) return;

    UserNode* user = ExistUser(UsersList, userName);
    if (!user) return;

    node->UID = user->UID;
    node->GID = user->GID;
    ChangeOwnerAll(node->LeftChild, userName);
    ChangeOwnerAll(node->RightChild, userName);
}

// target 경로 탐색 (for find)
int DirRead(DTree** tree, char* line, char* target, int flag) {
    char* tokens[12];
    char* ptr = strtok(line, " ");
    int i = 0;

    while (ptr && i < 12) {
        tokens[i++] = ptr;
        ptr = strtok(NULL, " ");
    }
    if (i < 11) return 0;

    char* name = tokens[0];
    char* path = tokens[11];
    path[strcspn(path, "\n")] = '\0';

    if ((flag == 0 && strstr(name, target)) || (flag == 1 && strstr(path, target))) {
        printf("%s/%s\n", strcmp(path, "/") == 0 ? "" : path, name);
    }
    return 0;
}