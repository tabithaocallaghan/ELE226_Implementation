
#include "../lib/Pin_manager.h"
#include "../lib/UserDatabase.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <unistd.h>
#include <ctype.h>

using namespace std;

int main(){
    PIN_manager crashout_T;
    crashout_T.validatePin();

    UserDB AuthDB;
    AuthDB.AddUser();
   
}

