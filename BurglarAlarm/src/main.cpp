#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ---------------- ENUMS ----------------
enum class UserRole { ADMIN, AUTH, UNAUTH };

// ---------------- USER CLASS ----------------
class User {
private:
    int userID;
    string name;
    string pin;
    UserRole role;

public:
    User(int id, string n, string p, UserRole r)
        : userID(id), name(n), pin(p), role(r) {}

    bool verifyCredential(string inputPin) {
        return inputPin == pin;
    }

    UserRole getRole() {
        return role;
    }
};

// ---------------- PIN MANAGER ----------------
class PinManager {
private:
    string storedPin = "1234";

public:
    bool validatePin(string input) {
        return input == storedPin;
    }
};

// ---------------- SENSOR BASE ----------------
class Sensor {
public:
    virtual bool read() {
        return false;
    }
};

// ---------------- DERIVED SENSORS ----------------
class DoorSensor : public Sensor {
public:
    bool read() override {
        cout << "[Sensor] Door checked.\n";
        return false;
    }
};

class WindowSensor : public Sensor {
public:
    bool read() override {
        cout << "[Sensor] Window checked.\n";
        return false;
    }
};

class PIRSensor : public Sensor {
public:
    bool read() override {
        cout << "[Sensor] Motion checked.\n";
        return false;
    }
};

// ---------------- ACTUATOR ----------------
class Actuator {
public:
    virtual void activate() {
        cout << "[Actuator] Activated\n";
    }

    virtual void deactivate() {
        cout << "[Actuator] Deactivated\n";
    }
};

// ---------------- BURGLAR ALARM SYSTEM ----------------
class BurglarAlarmSystem {
private:
    vector<Sensor*> sensors;
    vector<Actuator*> actuators;
    vector<User> users;

    PinManager pinManager;
    bool isArmed = false;

public:
    BurglarAlarmSystem() {
        // Add sensors
        sensors.push_back(new DoorSensor());
        sensors.push_back(new WindowSensor());
        sensors.push_back(new PIRSensor());

        // Add actuator (simple placeholder)
        actuators.push_back(new Actuator());
    }

    void addUser(User user) {
        users.push_back(user);
    }

    bool armSystem(string pin) {
        if (pinManager.validatePin(pin)) {
            isArmed = true;
            cout << "[System] Armed.\n";
            return true;
        }
        return false;
    }

    bool disarmSystem(string pin) {
        if (pinManager.validatePin(pin)) {
            isArmed = false;
            cout << "[System] Disarmed.\n";
            return true;
        }
        return false;
    }

    bool isSystemArmed() {
        return isArmed;
    }

    void pollSensors() {
        for (auto s : sensors) {
            if (s->read()) {
                triggerAlarm();
            }
        }
    }

    void processFaceRecognition(bool recognised) {
        if (recognised) {
            cout << "[FaceRecognition] Access granted.\n";
        } else {
            cout << "[FaceRecognition] Unknown face!\n";
            triggerAlarm();
        }
    }

    void triggerAlarm() {
        cout << "[ALARM] Intruder detected!\n";
        for (auto a : actuators) {
            a->activate();
        }
    }

    void displayStatus(string msg) {
        cout << "[STATUS] " << msg << endl;
    }

    void handleEntryGracePeriod() {
        cout << "[Timer] Entry grace check...\n";
    }

    void handleExitGracePeriod() {
        cout << "[Timer] Exit grace check...\n";
    }

    void checkDataRetention() {
        cout << "[Data] Checking retention...\n";
    }

    void deleteExpiredUserData() {
        cout << "[Data] Cleaning old data...\n";
    }
};

// ---------------- MAIN ----------------
int main()
{
    BurglarAlarmSystem system;

    // Add default user
    User admin(1, "Admin", "1234", UserRole::ADMIN);
    system.addUser(admin);

    string pin;
    char choice = 'Y';

    cout << "===== BURGLAR ALARM SYSTEM STARTED =====\n";

    while (choice == 'Y' || choice == 'y')
    {
        cout << "\nEnter PIN to ARM system: ";
        cin >> pin;

        if (!system.armSystem(pin)) {
            cout << "Invalid PIN.\n";
            continue;
        }

        while (system.isSystemArmed())
        {
            system.pollSensors();

            bool faceRecognised;
            cout << "\nFace recognised? (1 = yes, 0 = no): ";
            cin >> faceRecognised;

            system.processFaceRecognition(faceRecognised);

            system.handleEntryGracePeriod();
            system.handleExitGracePeriod();

            system.displayStatus("System running...");

            cout << "\nEnter PIN to DISARM (or 0 to continue): ";
            cin >> pin;

            if (pin != "0") {
                if (system.disarmSystem(pin)) {
                    break;
                } else {
                    cout << "Incorrect PIN.\n";
                }
            }
        }

        system.checkDataRetention();
        system.deleteExpiredUserData();

        cout << "\nRestart system? (Y/N): ";
        cin >> choice;
    }

    cout << "System shutdown.\n";
    return 0;
}