// Arduino Speedometer - Bicycle Configuration Example
// Configuration for bicycle with 26" wheel and spoke magnet sensor

// Pin configuration
const int signalPin = 2;           // Digital pin for pulse input

// Bicycle-specific configuration
const float wheelCircumference = 2.074; // 26" wheel circumference in meters
const int pulsesPerRevolution = 1;      // One magnet on spoke = 1 pulse per revolution

// Measurement settings
const unsigned long measurementInterval = 500;  // Update every 0.5 seconds for faster response
const int maxPulseRate = 100;     // Max expected pulses/sec for bicycle

// Display settings
const bool showDetailedOutput = true;   // Show max, avg, distance
const bool showMPH = false;            // Show km/h instead of mph

// --- Copy this configuration to your main code.ino file ---

/* 
 * Common bicycle wheel circumferences:
 * 20" wheel: 1.57 m
 * 24" wheel: 1.91 m  
 * 26" wheel: 2.074 m
 * 27" wheel: 2.155 m
 * 28" wheel: 2.23 m
 * 29" wheel: 2.29 m
 */