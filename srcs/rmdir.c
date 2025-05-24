#include "team6.h"

int rmdir_cmd(DTree* TreeDir, char* cmd) {
    if (!cmd) {
        printf("rmdir: missing operand\n");
        return -1;
    }

    TreeNode* origin = TreeDir->current;
    TreeNode* target = NULL;
    char tmp[MAX_DIR];
    strncpy(tmp, cmd, MAX_DIR);
    tmp[MAX_DIR - 1] = '\0';

    if (strchr(cmd, '/')) {
        char* parentPath = TakeDir(cmd);
        if (MovePath(TreeDir, parentPath) != 0) {
            printf("rmdir: cannot access '%s': No such directory\n", parentPath);
            return -1;
        }

        char* lastToken = strrchr(cmd, '/');
        lastToken = lastToken ? lastToken + 1 : cmd;
        target = DirExistion(TreeDir, lastToken, 'd');
    } else {
        target = DirExistion(TreeDir, cmd, 'd');
    }

    if (!target) {
        printf("rmdir: failed to remove '%s': No such directory\n", cmd);
        TreeDir->current = origin;
        return -1;
    }

    if (target->LeftChild != NULL) {
        printf("rmdir: failed to remove '%s': Directory not empty\n", target->name);
        TreeDir->current = origin;
        return -1;
    }

    if (OwnPermission(TreeDir->current, 'w') != 0 || OwnPermission(TreeDir->current, 'x') != 0) {
        printf("rmdir: permission denied\n");
        TreeDir->current = origin;
        return -1;
    }

    printf("rmdir: directory '%s' removed\n", target->name);
    DirRemove(target);
    TreeDir->current = origin;
    return 0;
}
