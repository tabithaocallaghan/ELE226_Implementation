#include "Pin_manager.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <unistd.h>
#include <ctype.h>
#include <chrono>
#include <thread>

using namespace std;

//constructor 1
PIN_manager::PIN_manager()
{
    storedPinAdd=&currentPIN;
    currentPIN=1234;
    maxAttempts=4;
    attemptCount=0;
    reset=0;
    userID=currentPIN;
    // time(&pin_timer.lock_Time);
    // ctime(&pin_timer.init_time);
    currentStatus=ENTER;
}

//constructor 2
PIN_manager::PIN_manager(string pin)
{
    currentPIN=stoi(pin);
}

void PIN_manager::resetAttempts()
{
    if(currentStatus==ENTER&&attemptCount==maxAttempts)
    {
    attemptCount=0;
    }
}

bool PIN_manager:: isLocked()
{
        int seconds=10;
        currentStatus=INVALID;
         system("clear");
        cout<<maxAttempts<<" attempts made. System locked for "<<seconds<<" seconds"<<endl;
        sleep(2);
        while(seconds>=1)
        {
            system("clear");
            cout<<"System is locked"<<endl;
            cout<<seconds<<" seconds remaining"<<flush;
            this_thread ::sleep_for(chrono:: seconds(1));
            //cout<<pin_timer.Time_diff;
            seconds--;
        }
        currentStatus=ENTER;
        return 0; //unlocked
        //sleep(pin_timer.lock_Time);
    }


enum PIN_manager:: PinStatus PIN_manager :: validatePin()
{   
    cout<<"Enter Pin"<<endl;
    cin>>user_input;
    while(currentStatus!=VALIDATED && attemptCount<4)
    {
    if (currentPIN==user_input)
    {
        cout<<"Correct Pin. Welcome (user name)"<<endl;
        currentStatus=VALIDATED;

    }
    else{
        cout<<"Incorrect PIN"<<endl;
        attemptCount=attemptCount+1;
        cout<<logFailedAttempts()<<endl;
        if(attemptCount==maxAttempts)
        {
            isLocked();
            resetAttempts();
            system("clear");
        }
        cout<<"Enter Pin"<<endl;
        cin>>user_input;
       
    }
    }
    return currentStatus;
}

int PIN_manager:: logFailedAttempts()
{
    return attemptCount;
}
void PIN_manager:: changePin(int newPin)
{
    bool authUser;
    cout<<"Enter user ID"<<endl;
    cin>>authUser;
    if(authUser)        //to be attached to userid database
    {
        *storedPinAdd=newPin;
        cout<<"New pin ";
        cout<<currentPIN<<endl;

    }
}


