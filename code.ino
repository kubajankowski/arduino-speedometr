// Arduino Speedometer - Enhanced Version
// Measures vehicle speed using pulse signals from wheel sensor

// Pin configuration
const int signalPin = 2;           // Digital pin for pulse input (must support interrupts)

// Global variables
volatile unsigned int pulses = 0;  // Pulse counter (modified in interrupt)
unsigned long previousTime = 0;    // Last measurement timestamp
unsigned long startTime = 0;       // System start time for total distance

// Vehicle configuration (easily adjustable for different setups)
const float wheelCircumference = 1.922; // Wheel circumference in meters (17" wheel, 225/40 tire)
const int pulsesPerRevolution = 48;     // Pulses per wheel revolution (pathfinder diff)

// Speed calculation variables
float currentSpeed = 0.0;          // Current speed in km/h
float maxSpeed = 0.0;              // Maximum recorded speed
float totalDistance = 0.0;         // Total distance traveled in km
float speedSum = 0.0;              // Sum for average calculation
int speedMeasurements = 0;         // Number of speed measurements

// Configuration
const unsigned long measurementInterval = 1000; // Measurement interval in milliseconds
const int maxPulseRate = 10000;    // Maximum expected pulses per second (safety check)      

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect (needed for native USB)
  }
  
  // Configure interrupt pin
  pinMode(signalPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(signalPin), countPulse, RISING);
  
  // Initialize timing
  previousTime = millis();
  startTime = millis();
  
  // Print startup message
  Serial.println("Arduino Speedometer Initialized");
  Serial.println("Wheel circumference: " + String(wheelCircumference) + " m");
  Serial.println("Pulses per revolution: " + String(pulsesPerRevolution));
  Serial.println("Measurement interval: " + String(measurementInterval) + " ms");
  Serial.println("======================================");
}

void loop() {
  unsigned long now = millis();
  
  // Check if it's time for a new measurement
  if (now - previousTime >= measurementInterval) {
    // Calculate time elapsed in seconds
    float timeElapsed = (now - previousTime) / 1000.0;
    
    // Create local copy of pulse count and reset (atomic operation)
    noInterrupts();
    unsigned int currentPulses = pulses;
    pulses = 0;
    interrupts();
    
    // Safety check for unrealistic pulse rates
    if (currentPulses > maxPulseRate) {
      Serial.println("Warning: Pulse rate too high, possible noise detected");
      currentPulses = 0; // Ignore this measurement
    }
    
    // Calculate current speed
    if (timeElapsed > 0) {
      float revolutions = (float)currentPulses / pulsesPerRevolution;
      float distanceMeters = revolutions * wheelCircumference;
      currentSpeed = (distanceMeters / timeElapsed) * 3.6; // Convert m/s to km/h
      
      // Update statistics
      updateStatistics(distanceMeters, timeElapsed);
      
      // Display results
      displaySpeedInfo();
    }
    
    previousTime = now;
  }
  
  // Small delay to prevent excessive CPU usage
  delay(10);
}

// Update speed and distance statistics
void updateStatistics(float distance, float timeElapsed) {
  // Update maximum speed
  if (currentSpeed > maxSpeed) {
    maxSpeed = currentSpeed;
  }
  
  // Update total distance (convert to kilometers)
  totalDistance += distance / 1000.0;
  
  // Update average speed calculation
  if (currentSpeed > 0.1) { // Only count non-zero speeds for average
    speedSum += currentSpeed;
    speedMeasurements++;
  }
}

// Display speed information to serial monitor
void displaySpeedInfo() {
  Serial.print("Speed: ");
  Serial.print(currentSpeed, 1);
  Serial.print(" km/h | Max: ");
  Serial.print(maxSpeed, 1);
  Serial.print(" km/h | Distance: ");
  Serial.print(totalDistance, 3);
  Serial.print(" km");
  
  // Calculate and display average speed
  if (speedMeasurements > 0) {
    float avgSpeed = speedSum / speedMeasurements;
    Serial.print(" | Avg: ");
    Serial.print(avgSpeed, 1);
    Serial.print(" km/h");
  }
  
  // Display uptime
  unsigned long uptime = (millis() - startTime) / 1000;
  Serial.print(" | Uptime: ");
  Serial.print(uptime);
  Serial.println("s");
}

// Interrupt service routine - increment pulse counter
void countPulse() {
  pulses++;
}
