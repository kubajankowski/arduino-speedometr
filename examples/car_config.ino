// Arduino Speedometer - Car Configuration Example
// Configuration for passenger car with 17" wheels and differential sensor

// Pin configuration
const int signalPin = 2;           // Digital pin for pulse input

// Car-specific configuration
const float wheelCircumference = 1.922; // 17" wheel, 225/40R17 tire
const int pulsesPerRevolution = 48;     // Differential sensor pulses per wheel revolution

// Measurement settings
const unsigned long measurementInterval = 1000; // Update every 1 second
const int maxPulseRate = 5000;    // Max expected pulses/sec for car (safety limit)

// Display settings
const bool showDetailedOutput = true;   // Show max, avg, distance
const bool showMPH = false;            // Show km/h instead of mph

// --- Copy this configuration to your main code.ino file ---