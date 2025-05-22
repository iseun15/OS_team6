#ifndef TEAM6_H
#define TEAM6_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

// 상수 정의
#define MAX_BUFFER 512
#define MAX_LENGTH 256
#define MAX_DIR 50
#define MAX_NAME 32
#define MAX_PASSWORD 32
#define MAX_THREAD 50

// 사용자 정보 구조체
typedef struct UserNode {
    char name[MAX_NAME];
    char password[MAX_PASSWORD];
    char dir[MAX_DIR];
    int UID;
    int GID;
    int year, month, day, wday, hour, min, sec;
    struct UserNode* LinkNode;
} UserNode;

// 사용자 목록 구조체
typedef struct UserTag {
    int tUID;
    int tGID;
    UserNode* head;
    UserNode* tail;
    UserNode* current;
} UserList;

// 디렉토리/파일 노드 구조체
typedef struct TreeNode {
    char name[MAX_NAME];
    char type;
    int mode;
    char permission[11];
    int SIZE;
    int UID, GID;
    int month, day, hour, min;
    int line;
    char* contents;
    char* owner;
    char* group;
    struct tm* time;
    struct TreeNode* Parent;
    struct TreeNode* LeftChild;
    struct TreeNode* RightChild;
    struct TreeNode* RightSibling;
} TreeNode;

// 디렉토리 트리 구조체
typedef struct DTreeTag {
    TreeNode* root;
    TreeNode* current;
} DTree;

// 스택 구조체
typedef struct StackNode {
    char name[MAX_NAME];
    struct StackNode* LinkNode;
} StackNode;

typedef struct StackTag {
    StackNode* TopNode;
} Stack;

// Thread용 구조체
typedef struct ThreadTag {
    DTree* MultiDTree;
    DTree* NodeFileName;
    char* command;
    char* PathCopy;
    char* AddValues;
    char AddValuesBuffer[MAX_NAME];
} ThreadTag;

// 전역 변수 선언
extern time_t ltime;
extern struct tm* Now;
extern UserList* UsersList;
extern FILE* User;
extern FILE* Dir;
extern DTree* Linux;
extern Stack* dStack;
extern TreeNode* lp;
extern char* arg[];
extern pthread_mutex_t tree_mutex;

// 함수 선언

// dir.c
int MovePath(DTree* dTree, const char* path);
TreeNode* ChangeToSubdirectory(TreeNode* current, const char* token);

// utility.c
int ModeToPermission(TreeNode* node);
void PermissionPrint(TreeNode* node);
void NodeRemove(TreeNode* node);
void DirRemove(TreeNode* node);
TreeNode* DirExistion(DTree* tree, const char* name, char type);
char* TakeDir(const char* path);
void TakePath(DTree* tree, TreeNode* node, Stack* stack);
void ModeConversAll(TreeNode* node, int mode);
void ChangeOwnerAll(TreeNode* node, char* userName);
int DirRead(DTree** tree, char* line, char* target, int flag);
void SaveNode(TreeNode* node);
void LoadNodes(void);

// user.c
void Login(UserList* userList, DTree* dTree);
UserList* UserListLoad(void);
void UserListSave(UserList* userList);
UserNode* ExistUser(UserList* list, const char* name);
int OwnPermission(TreeNode* node, char mode);

// stack.c
int IsEmpty(Stack* stack);
Stack* StackInitialization();
int Push(Stack* stack, const char* name);
char* Pop(Stack* stack);
void FreeStack(Stack* stack);
void PrintStack(Stack* stack);

// 명령어 함수
void adduser(char* argument, DTree* dirtree, UserList* userlist);
int mv(DTree* TreeDir, char* cmd);
int rmdir_cmd(DTree* TreeDir, char* cmd);
void cat(char* args);
void* cat_worker(void* arg);
void tail(char* args);
void* tail_worker(void* arg);
void clear(void);
void* clear_worker(void* arg);
int Mkdir(DTree* dirTree, char* cmd);
int MakeDir(DTree* dirTree, char* dirName, char type);
int chmod_(DTree* dirTree, char* cmd);
int pwd(DTree* dirTree, Stack* stack, char* cmd);
void PrintPath(DTree* dirTree, Stack* stack);
void ls(const char* option);
void cd(const char* path);
void echo(const char* args);

#endif // TEAM6_H
