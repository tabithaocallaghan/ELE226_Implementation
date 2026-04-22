// Sensor.cpp
// Implementation of the shared, non-abstract behaviour in the Sensor base class.
// The pure-virtual methods (refreshState, isTriggered, getType) are implemented
// by the concrete subclasses in their own .cpp files.

#include "Sensor.h"

// ---- Constructor ----
// Initialises every attribute to a safe default and configures the pin.
// The : syntax is a "member initialiser list" — it sets member values before
// the constructor body runs. It's the preferred way to initialise in C++.
Sensor::Sensor(int id, int pin)
    : sensorId(id),
      arduinoPin(pin),
      enabled(true),
      currentState(false),
      lastState(false),
      lastChangeMs(0)
{
    pinMode(arduinoPin, INPUT);
}

// ---- setEnabled ----
// Toggles whether this sensor should be polled.
// The AlarmController can use this to temporarily ignore a sensor
// (e.g. disable the window sensor during a known maintenance event).
void Sensor::setEnabled(bool on) {
    enabled = on;
}

// ---- isEnabled ----
// Returns whether the sensor is currently active.
bool Sensor::isEnabled() const {
    return enabled;
}

// ---- getState ----
// Returns the most recent hardware reading.
// Note: this does NOT re-read the pin — it just returns the cached value
// last stored by refreshState(). The controller decides when to refresh.
bool Sensor::getState() const {
    return currentState;
}

// ---- stateChanged ----
// Returns true if the latest refreshState() call detected an edge
// (i.e. currentState is different from lastState).
// Useful for detecting the moment an event starts — e.g. "door just opened".
bool Sensor::stateChanged() const {
    return currentState != lastState;
}

// ---- getLastChangeMs ----
// Returns the millis() timestamp at which the last state change occurred.
// Used for time-based logic (e.g. debouncing, entry-delay timing).
unsigned long Sensor::getLastChangeMs() const {
    return lastChangeMs;
}