#include "team6.h" // 여기서 tree_mutex는 extern으로 선언되어 있음

typedef struct {
    DTree* TreeDir;
    char src[MAX_DIR];
    char dst[MAX_DIR];
} MvArgs;

void* mv_thread(void* arg) {
    MvArgs* args = (MvArgs*)arg;
    DTree* TreeDir = args->TreeDir;
    char* src = args->src;
    char* dst = args->dst;

    char tmpSrc[MAX_DIR];
    strncpy(tmpSrc, src, MAX_DIR);
    tmpSrc[MAX_DIR - 1] = '\0';

    pthread_mutex_lock(&tree_mutex); // 락 시작

    TreeNode* srcNode = DirExistion(TreeDir, tmpSrc, 'f');
    if (!srcNode) srcNode = DirExistion(TreeDir, tmpSrc, 'd');
    if (!srcNode) {
        printf("mv: cannot stat '%s': No such file or directory\n", src);
        pthread_mutex_unlock(&tree_mutex);
        pthread_exit(NULL);
    }

    if (OwnPermission(TreeDir->current, 'w') != 0 || OwnPermission(srcNode, 'w') != 0) {
        printf("mv: permission denied\n");
        pthread_mutex_unlock(&tree_mutex);
        pthread_exit(NULL);
    }

    TreeNode* dstNode = DirExistion(TreeDir, dst, 'd');
    if (dstNode) {
        TreeNode* parent = srcNode->Parent;
        TreeNode* child = parent->LeftChild;
        if (child == srcNode) {
            parent->LeftChild = srcNode->RightSibling;
        } else {
            while (child && child->RightSibling != srcNode)
                child = child->RightSibling;
            if (child && child->RightSibling == srcNode)
                child->RightSibling = srcNode->RightSibling;
        }

        srcNode->Parent = dstNode;
        srcNode->RightSibling = NULL;

        if (dstNode->LeftChild == NULL) {
            dstNode->LeftChild = srcNode;
        } else {
            TreeNode* last = dstNode->LeftChild;
            while (last->RightSibling)
                last = last->RightSibling;
            last->RightSibling = srcNode;
        }

        printf("mv: moved '%s' into directory '%s'\n", tmpSrc, dst);
    } else {
        strncpy(srcNode->name, dst, MAX_NAME);
        srcNode->name[MAX_NAME - 1] = '\0';
        printf("mv: renamed '%s' to '%s'\n", tmpSrc, dst);
    }

    pthread_mutex_unlock(&tree_mutex); // 락 해제
    pthread_exit(NULL);
}

int mv(DTree* TreeDir, char* cmd) {
    if (!cmd) {
        printf("mv: missing file operand\n");
        return -1;
    }

    char* src = strtok(cmd, " ");
    char* dst = strtok(NULL, " ");

    if (!src || !dst) {
        printf("mv: missing destination operand\n");
        return -1;
    }

    pthread_t tid;
    MvArgs* args = malloc(sizeof(MvArgs));
    if (!args) {
        perror("malloc failed");
        return -1;
    }

    args->TreeDir = TreeDir;
    strncpy(args->src, src, MAX_DIR);
    strncpy(args->dst, dst, MAX_DIR);

    if (pthread_create(&tid, NULL, mv_thread, (void*)args) != 0) {
        perror("pthread_create failed");
        free(args);
        return -1;
    }

    pthread_join(tid, NULL);
    free(args);
    return 0;
}