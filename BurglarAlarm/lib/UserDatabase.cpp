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
    char* messageError;

    int exit = sqlite3_open("/Users/talentyolandandlovu/Documents/PlatformIO/Projects/ELE226_Implementation/BurglarAlarm/test/AuthUsers1.db", &db);

    if (exit)
    {
        cerr << "Error opening DB\n";
        return;
    }

    // 1. Create table
    string sql =
    "CREATE TABLE IF NOT EXISTS AUTH_USERS ("
    "USER_ID TEXT PRIMARY KEY NOT NULL,"
    "USER_FIRST_NAME TEXT NOT NULL,"
    "USER_LAST_NAME TEXT NOT NULL,"
    "AUTH_TYPE TEXT NOT NULL"
    ");";

    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK)
    {
        cerr << "Error creating table: " << messageError << endl;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Table ready\n";
    }

    sqlite3_close(db);
}
void UserDB::AdminInit()
{
    sqlite3* db;
    char* messageError;

    int exit = sqlite3_open("/Users/talentyolandandlovu/Documents/PlatformIO/Projects/ELE226_Implementation/BurglarAlarm/test/AuthUsers1.db", &db);

    // Insert multiple users
    string sql_insert[4] =
    {
        "INSERT OR IGNORE INTO AUTH_USERS VALUES('9999','YOLANDA','NDLOVU','ADMIN');",
        "INSERT OR IGNORE INTO AUTH_USERS VALUES('9998','TABITHA','O''CALLAGHAN','ADMIN');",
        "INSERT OR IGNORE INTO AUTH_USERS VALUES('9997','LETHABO','MELLO','ADMIN');",
        "INSERT OR IGNORE INTO AUTH_USERS VALUES('9996','ZIAD','MUBARAK','ADMIN');"
    };

    for (int i=0;i<=3;i++)
    {
        exit = sqlite3_exec(db, sql_insert[i].c_str(), NULL, 0, &messageError);

        if (exit != SQLITE_OK)
        {
            cerr << "Error inserting data: " << messageError << endl;
            sqlite3_free(messageError);
        }
        else
        {
            cout << "Insert successful\n";
        }
    }

    sqlite3_close(db);
}

void  UserDB :: AddUser()
{
createDB();
AdminInit();
}

void UserDB::removeUser()
{

}

void UserDB::ViewUsers()
{
    sqlite3* db;
    sqlite3_stmt* stmt;

    int rc = sqlite3_open("/Users/talentyolandandlovu/Documents/PlatformIO/Projects/ELE226_Implementation/BurglarAlarm/test/AuthUsers1.db", &db);

    if (rc)
    {
        std::cerr << "Error opening DB\n";
        return;
    }

    std::string sql = "SELECT USER_ID, USER_FIRST_NAME, USER_LAST_NAME, AUTH_TYPE FROM AUTH_USERS;";

    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    if (rc != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement\n";
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        std::string id = (const char*)sqlite3_column_text(stmt, 0);
        std::string first = (const char*)sqlite3_column_text(stmt, 1);
        std::string last = (const char*)sqlite3_column_text(stmt, 2);
        std::string type = (const char*)sqlite3_column_text(stmt, 3);

        std::cout << id << " | " << first << " | " << last << " | " << type << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

}
int UserDB::Auth_Pins()
    {
        int user_id;
        sqlite3* db;
        sqlite3_stmt* stmt;
        int rc= sqlite3_open("/Users/talentyolandandlovu/Documents/PlatformIO/Projects/ELE226_Implementation/BurglarAlarm/test/AuthUsers1.db",&db);
        
        if(rc)
        {
            cerr<<"Error opening DB\n";
            return false;
        }
        string sql=
        "SELECT * FROM AUTH_USERS WHERE USER_ID=?;";

        sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, user_id.c_str(), -1, SQLITE_STATIC);

    bool valid = false;

    if (sqlite3_step(stmt) == SQLITE_ROW)

    {
        valid = true;  // ID exists
    }

    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return valid;
}


