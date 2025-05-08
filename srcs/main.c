
#include "team6.h"

//전역 변수
time_t ltime; 
struct tm* Now; 
UserList* UsersList;   
FILE* User;    
FILE* Dir;
DTree* Linux;
Stack* dStack;


int main() {

    dStack = StackInitialization();
    UsersList = UserListLoad();

    Login(UsersList, Linux);
    UserListSave(UsersList);


    return 0;
}
