// Arduino Speedometer - Motorcycle Configuration Example
// Configuration for motorcycle with 17" wheel and ABS sensor

// Pin configuration
const int signalPin = 2;           // Digital pin for pulse input

// Motorcycle-specific configuration
const float wheelCircumference = 1.87;  // 17" wheel, 120/70R17 tire
const int pulsesPerRevolution = 24;     // ABS sensor pulses per wheel revolution

// Measurement settings
const unsigned long measurementInterval = 800;  // Update every 0.8 seconds
const int maxPulseRate = 8000;    // Max expected pulses/sec for motorcycle

// Display settings
const bool showDetailedOutput = true;   // Show max, avg, distance
const bool showMPH = false;            // Show km/h instead of mph

// --- Copy this configuration to your main code.ino file ---

/*
 * Common motorcycle tire circumferences (approximate):
 * Front 120/70R17: 1.87 m
 * Rear 180/55R17: 1.95 m
 * Front 110/80R19: 2.07 m
 * Rear 140/80R17: 1.93 m
 */