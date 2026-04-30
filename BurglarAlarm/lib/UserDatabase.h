//code for creating user database
#include <iostream>
#include <string>
#include <iostream>

using namespace std;

class UserDB
{
    private:
    int AuthNum;
    enum UserState
    {
        UNAUTHORISED,
        AUTHORISED,
    };
    bool FaceRec;
    struct AuthUser
    {
        string AuthID;
        string Auth_FirstName;
        string Auth_LastName;
        string AuthPin;
        enum Auth_TYPE
        {
            REGULAR,
            ADMIN
        };
    };

    vector <AuthUser> AuthUserList;
    void createDB();
    void AdminInit();
    public:
    UserDB();
    void AddUser();
    void removeUser();
    void ViewUsers();
    int Auth_Pins();

    
};

