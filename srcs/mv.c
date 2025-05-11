#include "team6.h"

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

    char tmpSrc[MAX_DIR];
    strncpy(tmpSrc, src, MAX_DIR);
    tmpSrc[MAX_DIR - 1] = '\0';

    TreeNode* srcNode = DirExistion(TreeDir, tmpSrc, 'f');
    if (!srcNode) srcNode = DirExistion(TreeDir, tmpSrc, 'd');
    if (!srcNode) {
        printf("mv: cannot stat '%s': No such file or directory\n", src);
        return -1;
    }

    if (OwnPermission(TreeDir->current, 'w') != 0 || OwnPermission(srcNode, 'w') != 0) {
        printf("mv: permission denied\n");
        return -1;
    }

    TreeNode* dstNode = DirExistion(TreeDir, dst, 'd');
    if (dstNode) {
        // 이동
        srcNode->Parent = dstNode;
        srcNode->RightChild = dstNode->LeftChild;
        dstNode->LeftChild = srcNode;
        printf("mv: moved '%s' into '%s'\n", tmpSrc, dst);
    } else {
        // 이름 변경
        strncpy(srcNode->name, dst, MAX_NAME);
        srcNode->name[MAX_NAME - 1] = '\0';
        printf("mv: renamed '%s' to '%s'\n", tmpSrc, dst);
    }

    return 0;
}


