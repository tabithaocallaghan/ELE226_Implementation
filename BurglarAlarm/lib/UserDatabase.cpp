#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "UserDatabase.h"
#include <sqlite3.h>

using namespace std;

UserDB::UserDB()
{
    AuthNum=0;
}

void UserDB::createDB()
{
    sqlite3* db;
    int exit=0;
    char* messageError;

    string sql="CREATE TABLE AUTH_USERS("
    "USER_ID TEXT PRIMARY KEY NOT NULL,"
    "USER_FIRST_NAME TEXT NOT NULL,"
    "USER_LAST_NAME TEXT NOT NULL,"
    "AUTH_TYPE ENUM('REGULAR','ADMIN'));";

    string sql_line("INSERT INTO AUTH_USERS VALUES(0204, YOLANDA, NDLOVU, ADMIN);");
    exit=sqlite3_open("/Users/talentyolandandlovu/Documents/PlatformIO/Projects/ELE226_Implementation/BurglarAlarm/AuthUsers.db",&db);
    exit=sqlite3_exec(db,sql.c_str(),NULL,0,&messageError);
     if(exit!=SQLITE_OK)
    {
        cerr<<"Error creating table"<<endl;//cerr allows the printing of a message to the console unbuffered
        sqlite3_free(messageError);
    }
    else{
        cout<<"Table created Successfully"<<endl;
        sqlite3_close(db);
    }

}

void  UserDB :: AddUser()
{
createDB();
}

void UserDB::removeUser()
{

}

void UserDB :: ViewUsers()
{

}

