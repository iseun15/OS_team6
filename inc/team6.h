//team6.h 의 모든 내용은 코드 짜면서 수정 필요함 (일단 가장 기본적인 것만 넣어둠)


//헤더 파일 안 쓴 거 나중에 삭제 + 쓰면서 계속 추가
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

//코드 짜면서 숫자 변경하기 
#define MAX_BUFFER 512
#define MAX_LENGTH 256 //문자열 길이 제한
#define MAX_DIR 50 //최대 디렉터리 수
#define MAX_NAME 32 //이름 최대 길이
#define MAX_PASSWORD 32
#define MAX_THREAD 50 



//사용자 정보
typedef struct UserNode {
    char name[MAX_NAME];
    char password[MAX_PASSWORD]; 
    char dir[MAX_DIR];
    int UID;  //user ID
    int GID;  //group ID
    int year;
    int month;
    int day;
    int wday; //요일
    int hour;
    int min;
    int sec;
    struct UserNode* LinkNode;
} UserNode;

//사용자 목록 관리
typedef struct UserTag{
    int tUID; //top UID
    int tGID; //top GID
    UserNode* head;
    UserNode* tail;
    UserNode* current;
} UserList;

//디렉토리 & 파일 정보 
typedef struct TreeNode{
    char name[MAX_NAME];
    char type;  // 디렉토리인지 파일인지 구분
    int mode; 
    int permission[9];
    int SIZE; //파일이면 byte크기, 디렉토리면 하위 노드 개수
    int UID;
    int GID;
    int month;
    int day;
    int hour;
    int min;

    int line;
    char* contents;
    char* owner;
    char* group;
    struct tm* time;

    struct TreeNode* Parent;
    struct TreeNode* LeftChild;
    struct TreeNode* RightChild;
}TreeNode;

extern TreeNode* lp;
extern char* arg[];

//디렉토리 트리 관리
typedef struct DTreeTag{
    TreeNode* root;
    TreeNode* current;
} DTree;


//스택 정보
typedef struct StackNode{
    char name[MAX_NAME];
    struct StackNode* LinkNode;
}StackNode;

// 스택 관리
typedef struct StackTag{
    StackNode* TopNode;
}Stack;

//thread 관리
typedef struct ThreadTag{
    DTree* MultiDTree;
    DTree* NodeFileName;
    char* command;
    char* PathCopy;
    char* AddValues;
}ThreadTag;

//전역변수
extern time_t ltime; //현재 시간
extern struct tm* Now; 
extern UserList* UsersList;   // 사용자 목록 포인터
extern FILE* User;    //사용자 파일 포인터
extern FILE* Dir;
extern DTree* Linux;
extern Stack* dStack;



//dir.c
int MovePath(DTree* dTree, const char* path);
TreeNode* ChangeToSubdirectory(TreeNode* current, const char* token);


//utility.c
int ModeToPermission(TreeNode* node); //권한
void PermissionPrint(TreeNode* node);
void NodeRemove(TreeNode* node); //삭제
void DirRemove(TreeNode* node); 
TreeNode* DirExistion(DTree* tree, const char* name, char type); //노드 탐색
char* TakeDir(const char* path); //경로 추출
void TakePath(DTree* tree, TreeNode* node, Stack* stack); 
void ModeConversAll(TreeNode* node, int mode); //모드 변경
void ChangeOwnerAll(TreeNode* node, char* userName); //소유자/그룹 변경
int DirRead(DTree** tree, char* line, char* target, int flag); //특정 경로 탐색

//user.c
void Login(UserList* userList, DTree* dTree);  //로그인
UserList* UserListLoad(void); //사용자 정보 관리
void UserListSave(UserList* userList);
UserNode* ExistUser(UserList* list, const char* name);
int OwnPermission(TreeNode* node, char mode); //권한 관리

//stack.c
int IsEmpty(Stack* stack);
Stack* StackInitialization();
int Push(Stack* stack, const char* name);
char* Pop(Stack* stack);
void FreeStack(Stack* stack);
void PrintStack(Stack* stack); //추후 제거 예정(디버깅용)

void cat(void);  // cat 명령어 함수 원형 선언
void* cat_worker(void* arg);
void clear(void);  // clear 명령어 함수
void* clear_worker(void* arg);
void head(void);  // head 명령어 함수
void* head_worker(void* arg);