// Sensor.h
// Abstract base class for every hardware sensor in the burglar alarm system.
// Defines the common interface so AlarmController can manage all sensors
// polymorphically (e.g. Sensor* sensors[]) without caring about concrete type.
//
// Concrete sensors (DoorSensor, WindowSensor, PIRSensor) inherit from this
// class and implement the pure-virtual methods refreshState() and isTriggered().

#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class Sensor {
protected:
    int           sensorId;        // Unique identifier for this sensor
    int           arduinoPin;      // Digital pin this sensor is connected to
    bool          enabled;         // Whether this sensor is currently active
    bool          currentState;    // Latest raw read from the hardware
    bool          lastState;       // Previous state — used to detect edges
    unsigned long lastChangeMs;    // millis() timestamp of the last state change

public:
    // Constructor: takes an ID and an Arduino pin number.
    Sensor(int id, int pin);

    // Virtual destructor: required so that `delete basePtr` correctly
    // destroys a derived-class object when using polymorphism.
    virtual ~Sensor() {}

    // ---- Common behaviour (shared by all sensors) ----
    void          setEnabled(bool on);
    bool          isEnabled() const;
    bool          getState() const;
    bool          stateChanged() const;
    unsigned long getLastChangeMs() const;

    // ---- Abstract behaviour (each concrete sensor MUST implement) ----

    // Reads the hardware and updates currentState / lastState / lastChangeMs.
    // Called every loop iteration by the AlarmController.
    virtual void refreshState(unsigned long nowMs) = 0;

    // Returns true if the sensor is in its "alarm-causing" condition:
    //   DoorSensor   → door open
    //   WindowSensor → window open
    //   PIRSensor    → motion detected
    virtual bool isTriggered() const = 0;

    // Short text label used for Serial logging (e.g. "Door", "Window", "PIR").
    virtual const char* getType() const = 0;
};

#endif