// Pins.h
// Centralised pin-assignment table for the Group 19 burglar alarm system.
// IMPORTANT: every Arduino pin used anywhere in the project is listed here.
// Do NOT hard-code pin numbers in other files — always reference Pins::X.
// This prevents two classes from accidentally using the same pin.

#ifndef PINS_H
#define PINS_H

namespace Pins {
    // ---- Sensors (digital inputs) ----
    constexpr int DOOR_SWITCH   = 2;   // RS Pro magnetic switch on the protected door
    constexpr int WINDOW_SWITCH = 3;   // RS Pro magnetic switch on the protected window
    constexpr int PIR_MOTION    = 4;   // TruSens HC-SR505 PIR (output stays HIGH for ~8s)

    // ---- Actuators (digital outputs) ----
    constexpr int BUZZER        = 8;   // RS PRO piezo buzzer
    constexpr int SOLENOID_LOCK = 9;   // Pimoroni COM2700 via BD911 NPN + flyback diode

    // ---- Status LEDs (one-at-a-time state indicator) ----
    constexpr int LED_DISARMED  = 10;  // Green
    constexpr int LED_DELAY     = 11;  // Amber / yellow — entry or exit delay active
    constexpr int LED_ARMED     = 12;  // Blue
    constexpr int LED_ALARM     = 13;  // Red (also the on-board LED on the Mega)

    // ---- Panic button (APEM PHAP3301) ----
    constexpr int PANIC_BUTTON  = 7;   // Optional: instant-arm, or for test mode
}

#endif