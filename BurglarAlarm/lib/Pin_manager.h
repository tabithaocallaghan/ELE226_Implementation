#include <string>
#include <iostream>
#include <ctime>

using namespace std;

class PIN_manager
{
private:
    int *storedPinAdd;
    int currentPIN;
    int maxAttempts;
    int attemptCount;
    bool reset;
    int user_input;
    string userID; //currently using this before creation of database
   
    enum PinStatus
    {
        ENTER,
        VALIDATED,
        INVALID
    };

    struct Time
    {
        time_t init_time;
        time_t current_Time;
        time_t lock_Time; 
        time_t Time_diff;
    };

    Time pin_timer;
    enum PinStatus currentStatus;
    void resetAttempts();
    bool isLocked();

public:
    //constructors
    PIN_manager();
    PIN_manager( string );

    //methods
    enum PinStatus validatePin();
    int logFailedAttempts();
    
    void changePin(int newPin);
};